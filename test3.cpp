
#define FMT_HEADER_ONLY
//#define BOOST_NO_MEMBER_TEMPLATES


#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>

#include <mariadb/conncpp.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/composite_key.hpp>


using namespace boost;
using namespace boost::multi_index;

/*Record of rtyAssignmetStatusHistory*/
struct RtyStatus {
    int id;
    std::string date;
    int rangeId;
    int rty;
    std::string campname;

    bool operator<(const RtyStatus& p) const { return id < p.id; }; 

    bool operator==(const RtyStatus& p) const
    {
        return
            this->date == p.date &&
            this->rangeId == p.rangeId &&
            this->rty == p.rty &&
            this->campname == p.campname;
    }
};

/*Custom Hash for Data of RtyStatus*/
struct DataRtyHash
{
    std::size_t operator()(const RtyStatus& drty)const
    {
        return
            boost::hash<std::string>()(drty.date) ^
            boost::hash<int>()(drty.rangeId) ^
            boost::hash<int>()(drty.rty) ^
            boost::hash<std::string>()(drty.campname);
    }
};

struct rtyRangeId {}; 

/*Multiply container with different index*/
typedef multi_index_container<
    RtyStatus,
    indexed_by<
        //ordered_unique<identity<RtyStatus>>,
        ordered_unique<member<RtyStatus, int, &RtyStatus::id>>,
        hashed_unique<identity<RtyStatus>, DataRtyHash>,
        ordered_non_unique<
            tag<rtyRangeId>,
            composite_key<
                    RtyStatus,
                    member<RtyStatus, int, &RtyStatus::rty>,
                    member<RtyStatus, int, &RtyStatus::rangeId>
            >,
            composite_key_compare<
                std::greater<int>,
                std::greater<int> 
            >
        >
  >
> RtyStatus_set;


/* Conex DB test mariadb*/
std::unique_ptr<sql::Connection> getConnDB();

/*load table RtyStatus in multiIndex container*/ 
RtyStatus_set getRtyStatus(sql::Connection *conn);

/*print in console */
void printRty(const RtyStatus rty); 


std::unique_ptr<sql::Connection> getConnDB() {
    try {
        // Instantiate Driver
        sql::Driver* driver = sql::mariadb::get_driver_instance();

        // Establish Connections
        // Use a smart pointer for extra safety
        // connex with root for simplicy
        std::unique_ptr<sql::Connection> conn(driver->connect("jdbc:mariadb://localhost:3306/testrtybd", "root", "root"));

        return conn; 
    } 
    // Catch Exceptions
    catch (sql::SQLException& e) {
        std::cerr << "Error Connecting to the database: "
            << e.what() << std::endl;
        return NULL; 
    }
}

RtyStatus_set getRtyStatus(sql::Connection* conn) {

    RtyStatus currentRecord;
    RtyStatus_set rs; 

    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("select * from rtyassignmentstatushistory"));

    sql::ResultSet* res = stmnt->executeQuery();

    while (res->next()) {

        //auto currentRecord = new RtyStatus((int) res->getInt(1), (std::string) res->getString(2), (int) res->getInt(3), (int) res->getInt(4), (std::string) res->getString(5)); 
       
        currentRecord.id = res->getInt(1);
        currentRecord.date = res->getString(2);
        currentRecord.rangeId = res->getInt(3);
        currentRecord.rty = res->getInt(4);
        currentRecord.campname = res->getString(5);
       
        rs.insert(currentRecord);
    }

    delete res; 

    return rs;
};


void printRty(const RtyStatus rty) {
    fmt::text_style color; 
    
    if (rty.id % 2 == 0) {
        color = fg(fmt::color::dark_red); 
    }
    else {
        color = fg(fmt::color::dark_green);
    }   

    fmt::print(color, "Id: {}, date:{}, rangeId: {}, rty:{}, campname:{}\n", rty.id, rty.date, rty.rangeId, rty.rty, rty.campname); 
};



void exercise3() {

    std::unique_ptr<sql::Connection> conn;
    RtyStatus_set rs;
    int count = 0;
 
    conn = getConnDB();
    if (conn) {
        rs = getRtyStatus(conn.get());
    }
 
    const RtyStatus_set::nth_index<0>::type& id_index = rs.get<0>();
    const RtyStatus_set::nth_index<2>::type& compIndex = rs.get<2>();

    auto p = id_index.find(568);

    for (auto iter = compIndex.begin(); iter != compIndex.end(); ++iter, ++count) {
        printRty(*iter);
    }

    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "\n\n TOTAL ROWS: {}", count);
}; 


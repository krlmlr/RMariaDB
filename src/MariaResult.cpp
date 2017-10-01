#include "pch.h"

#include "MariaResult.h"
#include "MariaResultPrep.h"

MariaResult::MariaResult(MariaConnectionPtr maria_conn_) : maria_conn(maria_conn_) {
}

MariaResult::~MariaResult() {
}

void MariaResult::set_current_result() {
  maria_conn->set_current_result(this);
}

void MariaResult::clear_current_result() {
  maria_conn->set_current_result(NULL);
}

MYSQL* MariaResult::get_conn() const {
  return maria_conn->get_conn();
}

bool MariaResult::active() const {
  return maria_conn->is_current_result(this);
}

void MariaResult::autocommit() {
  maria_conn->autocommit();
}

MariaResult* MariaResult::create_and_send_query(MariaConnectionPtr con, const std::string& sql) {
  std::auto_ptr<MariaResult> res(new MariaResultPrep(con));
  try {
    res->send_query(sql);
  }
  catch (MariaResultPrep::UnsupportedPS e) {
    stop("Not yet implemented");
  }

  return res.release();
}

#pragma once
#include "python_env.h"
#include "python_updater.h"
#include "shared_model.h"

namespace PS {

class PythonServer : public App {
public:
  PythonServer(PythonEnv* py_env) : App(), py_env_(py_env) {
    // This instance takes the ownership of py_env

    updater_ = new PythonUpdater<float>(py_env_);
    shared_model_ = new SharedModel<float>();
    shared_model_->setUpdater(updater_);
  }

  virtual void init() {
    try {
      if (py_env_->globals().has_key("server_node_init"))
        py_env_->globals().get("server_node_init")();
    } catch (boost::python::error_already_set) {
      PyErr_Print();
      throw;
    }
  }

  virtual ~PythonServer() {
    delete updater_;
    delete shared_model_;
    delete py_env_;
  }

private:
  PythonEnv* py_env_;
  Updater<float> *updater_;
  SharedModel<float> *shared_model_;
};

} // namespace PS


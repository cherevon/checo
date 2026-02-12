#include "checo/logging/log.h"

namespace checo::logging
{

class CHECO_LOGGING_EXPORT LogStdOut : public Log
{
  public:
    LogStdOut();
    ~LogStdOut() override;

  protected:
    void doWrite(const Level level, const std::string &message) override;
};
} // namespace checo::logging
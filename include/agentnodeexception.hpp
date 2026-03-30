#ifndef AGENTNODEEXCEPTION_H_INCLUDED
#define AGENTNODEEXCEPTION_H_INCLUDED

#include <exception>

class AgentNodeException : public std::exception {
            private:
                std::string msg;

            public:
                AgentNodeException()noexcept : msg("Error indefinido") {}

                AgentNodeException(const AgentNodeException& ex) noexcept : msg(ex.msg) {}

                AgentNodeException(const std::string& m) : msg(m) {}

                AgentNodeException& operator = (const AgentNodeException& ex) noexcept {
                    msg = ex.msg;
                    return *this;
                    }

                virtual ~AgentNodeException() {}

                virtual const char* what() const noexcept {
                    return msg.c_str();
                    }
            };

#endif // AGENTNODEEXCEPTION_H_INCLUDED

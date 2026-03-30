#ifndef AGENTLISTEXCEPTION_HPP_INCLUDED
#define AGENTLISTEXCEPTION_HPP_INCLUDED

#include <exception>

class AgentListException : public std::exception {
            private:
                std::string msg;

            public:
                AgentListException()noexcept : msg("Error indefinido") {}

                AgentListException(const AgentListException& ex) noexcept : msg(ex.msg) {}

                AgentListException(const std::string& m) : msg(m) {}

                AgentListException& operator = (const AgentListException& ex) noexcept {
                    msg = ex.msg;
                    return *this;
                    }

                virtual ~AgentListException() {}

                virtual const char* what() const noexcept {
                    return msg.c_str();
                    }
            };

#endif // AGENTLISTEXCEPTION_HPP_INCLUDED

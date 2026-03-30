#ifndef SL_NODE_HPP_INCLUDED
#define SL_NODE_HPP_INCLUDED

#include <exception>
#include <string>
#include "call.hpp"

//class Node; //forward declaration


class CallNode {
    public:
        typedef CallNode* Position;
    private:
        Call* dataPtr;
        Position next;
    public:
        // NODE EXCEPTION *****
        class CallNodeException : public std::exception {
            private:
                std::string msg;

            public:
                CallNodeException()noexcept : msg("Error indefinido") {}

                CallNodeException(const CallNodeException& ex) noexcept : msg(ex.msg) {}

                CallNodeException(const std::string& m) : msg(m) {}

                CallNodeException& operator = (const CallNodeException& ex) noexcept {
                    msg = ex.msg;
                    return *this;
                    }

                virtual ~CallNodeException() {}

                virtual const char* what() const noexcept {
                    return msg.c_str();
                    }
            };
        // CONSTRUCTORS
        CallNode();
        CallNode(const Position&);
        CallNode(const Call&);
        CallNode(Call*);
        //GETTERS
        Call getData()const;
        Position getNext()const;
        Call* getDataPtr()const;
        //SETTERS
        void setData(const Call&);
        void setNext(const Position&);
        void setDataPtr(Call*);
    };


#endif // SL_NODE_HPP_INCLUDED

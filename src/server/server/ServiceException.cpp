#include "ServiceException.h"

using namespace std;
using namespace server; 


ServiceException::ServiceException(HttpStatus status, std::string message):httpStatus(status),message(message){

}



HttpStatus ServiceException::getStatus(){
    return httpStatus;
}



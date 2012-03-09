// StubMarket.h
#if !defined(_STUBMARKET_H)
#define _STUBMARKET_H

#include "Logger.h"
#include "MarketModel.h"

/**
  @class StubMarket

  @brief This MarketModel is intended 
  as a skeleton to guide the implementation of new MarketModel models. 
  
  The StubMarket class inherits from the MarketModel class and is 
  dynamically loaded by the Model class when requested.
  
  @section intro Introduction
  Place an introduction to the model here. 

  @section modelparams Model Parameters
  Place a description of the required input parameters which define the model 
  implementation.

  @section optionalparams Optional Parameters
  Place a description of the optional input parameters to define the model 
  implementation.

  @section detailed Detailed Behavior
  Place a description of the detailed behavior of the model. Consider describing 
  the behavior at the tick and tock as well as the behavior upon sending and
  receiving materials and messages. 
 */
class StubMarket : public MarketModel {
/* --------------------
 * all MODEL classes have these public members
 * --------------------
 */
 public:
  /**
   * @brief Default constructor for StubMarket Class
   */
  StubMarket();

  /**
   * @brief every model should be destructable
   */
  virtual ~StubMarket();
    
  /**
   * @brief every model needs a method to initialize from XML
   *
   * @param cur is the pointer to the model's xml node 
   */
  virtual void init(xmlNodePtr cur);
  
  /**
   * @brief every model needs a method to copy one object to another
   *
   * @param src is the StubStub to copy
   */
  virtual void copy(StubMarket* src);

  /**
   * @brief This drills down the dependency tree to initialize all relevant parameters/containers.
   *
   * Note that this function must be defined only in the specific model in question and not in any 
   * inherited models preceding it.
   *
   * @param src the pointer to the original (initialized ?) model to be copied
   */
  virtual void copyFreshModel(Model* src);

  /**
   * @brief every model should be able to print a verbose description
   */
   virtual void print();

/* ------------------- */ 


/* --------------------
 * all COMMUNICATOR classes have these members
 * --------------------
 */
 public:
   /**
    * @brief The StubMarket should ignore incoming messages
    */
   virtual void receiveMessage(msg_ptr msg);
   
/* -------------------- */


/* --------------------
 * all MARKETMODEL classes have these members
 * --------------------
 */
 public:
   /**
    * @brief  Primary funcation of a Market is to resolve the set of 
    *  requests with the set of offers.
    *
    *  In this stub - do nothing!
    */
   virtual void resolve();

/* -------------------- */


/* --------------------
 * _THIS_ MARKETMODEL class these members
 * --------------------
 */

/* -------------------- */

};

#endif

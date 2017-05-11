/* Chatter.h
 * Owen Monsma
 * 25 April 2017
 */

#ifndef Chatter_hpp
#define Chatter_hpp

#include <string>
#include <iostream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#define CHAT_SIZE 64
#define MAX_RESPS 6

class Chatter{
public:
  Chatter();
  ~Chatter();

  struct Resp {
    Resp();

    std::string line;
    int next;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version){
      ar & line;
      ar & next;
    }
  };

  struct Node {
    Node();

    int nodeID;
    std::string line;
    int resps;
    Resp next[MAX_RESPS];

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version){
      ar & nodeID;
      ar & line;
      ar & resps;
      ar & next;
    }
  };

  Chatter(char* file);

  /** Returns formatted string for specified node ID */
  std::string print(int n);

  /** Returns pointer to node at given index */
  Node* getNode(int id);

  /** Adds a new conversation node and returns its ID or -1 on fail */
  int addNode(std::string line);

  /** Adds a new blank conversation node at specified index */
  int addNode(int index);

  /** Removes specified node, returning the index or -1 on fail */
  int removeNode(int id);

  /** Adds a new response to the specified node ID or -1 on fail */
  int addResp(int id, std::string line, int next);

  /** Removes response from node returning -1 on fail */
  int removeResp(int nodeID, int respID);

  void chat();

  /** Saves the current chat to the specified file */
  void saveChat(std::string filename);

  /** Loads chat from the specified file */
  void loadChat(std::string filename);

private:

  bool nodeExists(int id);

  Node nodeArr[CHAT_SIZE];

  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version){
    ar & nodeArr;
  }

};

#endif

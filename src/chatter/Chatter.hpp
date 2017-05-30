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

class Chatter {
  public:
    Chatter();
    ~Chatter();

    struct Resp {
      Resp();

      std::string line;
      int next;

      template <class Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
          (void)version;
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
        void serialize(Archive& ar, const unsigned int version)
        {
          (void)version;
          ar & nodeID;
          ar & line;
          ar & resps;
          ar & next;
        }
    };

    Chatter(char* file);

    /** Returns formatted string for specified node ID */
    std::string print(const int n);

    /** Returns pointer to node at given index */
    Node* getNode(const int id);

    /** Adds a new conversation node and returns its ID or -1 on fail */
    int addNode(const std::string line);

    /** Adds a new blank conversation node at specified index */
    int addNode(const int index);

    /** Removes specified node, returning the index or -1 on fail */
    int removeNode(const int id);

    /** Adds line to specified node */
    void addLineToNode(const int id, const std::string line);

    /** Returns line of specified node */
    std::string getLineFromNode(const int id) const;

    /** Adds a new response to the specified node ID or -1 on fail */
    int addResp(const int nodeID, const std::string line, const int next);

    int replaceResp(const int nodeID, const int respID, const std::string line);

    /** Removes response from node returning -1 on fail */
    int removeResp(const int nodeID, const int respID);

    void chat();

    /** Saves the current chat to the specified file */
    void saveChat(const std::string filename);

    /** Loads chat from the specified file */
    void loadChat(const std::string filename);

  private:

    bool nodeExists(int id) const;

    Node nodeArr[CHAT_SIZE];

    friend class boost::serialization::access;
    template <class Archive>
      void serialize(Archive& ar, const unsigned int version)
      {
        (void)version;
        ar & nodeArr;
      }

};

#endif

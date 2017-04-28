/* Chatter.h
 * Owen Monsma
 * 25 April 2017
 */

class Chatter{
public:
  Chatter();
  ~Chatter();

  Chatter(char* file);

  /** Returns formatted string for specified node ID */
  char* print(int n);

  /** Adds a new response to the specified node ID */
  int addResponse(int id, char* line, int next);

private:
  typedef struct Node {
    int nodeID = -1;
    char* line;
    int resps = 0;
    int[numResps] next;
  } Node;

  typedef struct Edge {
    char* line;
    int next;
  } Edge;

  Node* nodeArr;
  Edge* edgeArr;

  const int chatSize;
  const int maxResps;
}

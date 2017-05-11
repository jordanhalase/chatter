# Chatter

### A branching dialogue system for C++ games

Chatter is a static library and a collection of tools that gives an easy way to create branching dialogue tree systems for games.

## Editor basics

The editor window is broken into two sections: the large upper area is the viewing and editing area where the current chat node is displayed, as well as a linked next node. Below that is a black bar which shows the "timeline". Each asterisk in the timeline represents one node of the conversation, and the caret underneath shows which node you are currently editing.

```
+--------------------------------------------------------------------------------+
| VIEW                                                                           |
| +----------------------------------------------------------------------------+ |
| |   This is an example line of dialogue in the editor.                       | |
| | > 1. This is the first response. Its link is shown below.                  | |
| |   2.                                                                       | |
| |   3.                                                                       | |
| |   4.                                                                       | |
| |   5.                                                                       | |
| |   6.                                                                       | |
| +----------------------------------------------------------------------------+ |
|                                                                                |
| +----------------------------------------------------------------------------+ |
| | > This is the node that response 1 links to above.                         | |
| |   1. A response can be here.                                               | |
| |   2. It can be here as well.                                               | |
| |   3.                                                                       | |
| |   4.                                                                       | |
| |   5.                                                                       | |
| |   6.                                                                       | |
| +----------------------------------------------------------------------------+ |
| >System msgs                                                                   |
| :Prompt area                                                                   |
|!*********!*****************************************************                |
|^         $                                                                     |
+--------------------------------------------------------------------------------+

```

### View Mode

By default, the editor is set to **view** mode. In view mode, the user can easily browse through the loaded chat. View mode has the following controls:

| Key | Function |
| --- | -------- |
| [ | Cycle current node left |
| ] | Cycle current node right |
| Enter | Enter edit mode on current node |
| Arrow up/down | Select which response to view next from |
| s | Save the current chat. Prompts for filename |
| l | Loads a chat. Prompts for filename |
| q | Quits editor. Prevents quitting with unsaved changes |
| Q | Quits editor, discarding unsaved changes |


Pressing [ and ] will change the current node. When an empty node (marked * on the timeline) is chosen, pressing Enter will create a chat node there. Its symbol will change from * to ! on the timeline to show it is now a node, and the editor will go into edit mode.

### Edit Mode

The editor switches to **edit** mode when the user wants to change the text on a given node.

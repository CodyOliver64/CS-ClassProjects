// Cody Oliver
// COP 3503, Fall 2019

// ====================
// Skip Lists
// ====================

import java.io.*;
import java.util.*;

// Node class to store data and an array of pointers to the next node
class Node<AnyType>
{
  AnyType data;
  ArrayList<Node<AnyType>> pointerList;

  Node(int height)
  {
    pointerList = new ArrayList<Node<AnyType>>();

    // Initialize the pointer array with null references
    for (int i = 0; i < height; i++)
      pointerList.add(null);
  }

  Node(AnyType data, int height)
  {
    pointerList = new ArrayList<Node<AnyType>>(height);

    // Initialize the pointer array with null references
    for (int i = 0; i < height; i++)
      pointerList.add(null);

    this.data = data;
  }

  public AnyType value()
  {
    return data;
  }

  public int height()
  {
    return pointerList.size();
  }

  public Node<AnyType> next(int level)
  {
    if (level < 0 || level > pointerList.size() - 1)
      return null;

    return pointerList.get(level);
  }

  public void setNext(int level, Node<AnyType> node)
  {
    pointerList.set(level, node);
  }

  // Functions to Grow and Trim the height of nodes
  public void grow()
  {
    pointerList.add(null);
  }

  public boolean maybeGrow()
  {
    if (Math.random() < 0.5)
    {
      pointerList.add(null);
      return true;
    }
    return false;
  }

  public void trim(int height)
  {
    for (int i = 0; i < pointerList.size() - height; i++)
    {
      pointerList.remove(pointerList.size() - 1);
    }
  }

  public void trim()
  {
    pointerList.remove(pointerList.size() - 1);
  }
}

public class SkipList<AnyType extends Comparable<AnyType>>
{
  Node<AnyType> headNode;
  int size = 1;

  SkipList()
  {
    headNode = new Node<AnyType>(1);
  }

  // Constructor that creates a new head node with a specific height
  SkipList(int height)
  {
    if (height < 1)
      headNode = new Node<AnyType>(1);
    else
      headNode = new Node<AnyType>(height);
  }

  //  Returns the number of nodes in the SkipList (minus 1 so we don't count the head node)
  public int size()
  {
    return size - 1;
  }

  public int height()
  {
    return headNode.pointerList.size();
  }

  public Node<AnyType> head()
  {
    return headNode;
  }

  // An insert function where the height of the new node is given
  public void insert(AnyType data, int height)
  {
    Node<AnyType> currentNode = this.headNode;
    ArrayList<Node<AnyType>> dropPoints = new ArrayList<Node<AnyType>>();

    // Check if this new data comes directly after the head node, if so link them and exit
    if (headNode.pointerList.get(0) == null ||
                                            headNode.pointerList.get(0).data.compareTo(data) >= 0)
    {
      // Create new node with passed data
      Node<AnyType> newNode = new Node<AnyType>(data, height);

      // Loop down through the node, linking all pointers
      for (int i = newNode.height() - 1; i >= 0; i--)
      {
        newNode.pointerList.set(i, headNode.pointerList.get(i));
        headNode.pointerList.set(i, newNode);
      }

      // Increase the size of our Skip list and check if we need to grow the height
      size++;
      if (getMaxHeight(this.size()) > headNode.pointerList.size())
        growSkipList();
      return;
    }

    // Find where we should insert by creating our dropPoints list
    // Our drop points will tell us which pointers need to be linked to the new node
    for (int i = headNode.height() - 1; i >= 0; i--)
    {
      // Drop down if our pointer is null or if the data its pointing too is greater
      if (currentNode.pointerList.get(i) == null
                                      || currentNode.pointerList.get(i).data.compareTo(data) >= 0)
      {
        dropPoints.add(0, currentNode);
      }
      // Skip through to the next node on this level otherwise
      else
      {
        currentNode = currentNode.pointerList.get(i);
        i++;
      }
    }

    // Create our new node and link it up using the dropPoints
    Node<AnyType> newNode = new Node<AnyType>(data, height);

    for (int i = newNode.height() - 1; i >= 0; i--)
    {
      newNode.pointerList.set(i, dropPoints.get(i).pointerList.get(i));
      dropPoints.get(i).pointerList.set(i, newNode);
    }

    // Increase the size of our Skip list and check if we need to grow the height
    size++;
    if (getMaxHeight(this.size()) > headNode.pointerList.size())
      growSkipList();
    return;
  }

  // The main insert function where the height of our nodes are random
  public void insert(AnyType data)
  {
    Node<AnyType> currentNode = this.headNode;
    ArrayList<Node<AnyType>> dropPoints = new ArrayList<Node<AnyType>>();

    // Check if this new data comes directly after the head node, if so link them and exit
    if (headNode.pointerList.get(0) == null ||
                                            headNode.pointerList.get(0).data.compareTo(data) >= 0)
    {
      // Create new node with passed data
      Node<AnyType> newNode = new Node<AnyType>
                                          (data, generateRandomHeight(getMaxHeight(this.size())));

      // Loop down through the node, linking all pointers
      for (int i = newNode.height() - 1; i >= 0; i--)
      {
        newNode.pointerList.set(i, headNode.pointerList.get(i));
        headNode.pointerList.set(i, newNode);
      }

      // Increase the size of our Skip list and check if we need to grow the height
      size++;
      if (getMaxHeight(this.size()) > headNode.pointerList.size())
        growSkipList();
      return;
    }

    // Find where we should insert by creating our dropPoints list
    // Our drop points will tell us which pointers need to be linked to the new node
    for (int i = headNode.height() - 1; i >= 0; i--)
    {
      // Drop down if our pointer is null or if the data its pointing too is greater
      if (currentNode.pointerList.get(i) == null ||
                                          currentNode.pointerList.get(i).data.compareTo(data) >= 0)
      {
        dropPoints.add(0, currentNode);
      }
      // Skip through to the next node on this level otherwise
      else
      {
        currentNode = currentNode.pointerList.get(i);
        i++;
      }
    }

    // Create our new node and link it up using the dropPoints
    Node<AnyType> newNode = new Node<AnyType>
                                          (data, generateRandomHeight(getMaxHeight(this.size())));

    for (int i = newNode.height() - 1; i >= 0; i--)
    {
      newNode.pointerList.set(i, dropPoints.get(i).pointerList.get(i));
      dropPoints.get(i).pointerList.set(i, newNode);
    }

    // Increase the size of our Skip list and check if we need to grow the height
    size++;
    if (getMaxHeight(this.size()) > headNode.pointerList.size())
      growSkipList();
    return;
  }

  // Returns true if the data is in the SkipList, false otherwise
  public boolean contains(AnyType data)
  {
    int index = headNode.height() - 1;
    Node<AnyType> currentNode = headNode;

    //Loop through the height of the skip list
    while (index >= 0)
    {
      // If our tallest pointer is null, drop down
      if (currentNode.pointerList.get(index) == null)
      {
        index--;
      }
      // If our search value is greater than our current data, skip foward
      else if (currentNode.pointerList.get(index).data.compareTo(data) < 0)
      {
        currentNode = currentNode.pointerList.get(index);
      }
      // If our search value is less than our current data, drop down
      else if (currentNode.pointerList.get(index).data.compareTo(data) > 0)
      {
        index--;
      }
      // Getting here means we have found the data;
      else
        return true;
    }
    // Getting here means the data is not in the tree
    return false;
  }

  // Returns the reference to the node that contains the given data, or null if not in the list
  public Node<AnyType> get(AnyType data)
  {
    int index = headNode.height() - 1;
    Node<AnyType> currentNode = headNode;

    // An array to hold duplicates of the given data
    ArrayList<Node<AnyType>> getList = new ArrayList<Node<AnyType>>();

    // Start the list at null, to return null if the data is not found
    getList.add(null);

    //Loop through the height of the skip list
    while (index >= 0)
    {
      // If our tallest pointer is null, drop down
      if (currentNode.pointerList.get(index) == null)
      {
        index--;
      }
      // If our search value is greater than our current data, skip foward
      else if (currentNode.pointerList.get(index).data.compareTo(data) < 0)
      {
        currentNode = currentNode.pointerList.get(index);
      }
      // If our search value is less than our current data, drop down
      else if (currentNode.pointerList.get(index).data.compareTo(data) > 0)
      {
        index--;
      }
      // Getting here means we have found the data;
      else
      {
        getList.add(0, currentNode.pointerList.get(index));
        index--;
      }
    }
    // Returns the left most instance of the node with the given data
    return getList.get(0);
  }

  public void delete(AnyType data)
  {
    int index;
    Node<AnyType> currentNode;
    Node<AnyType> deleteNode;

    // Call the Get method to return a reference to the node to be deleted, null if not in the list
    deleteNode = this.get(data);

    // If our delete node was never found, do not run the loop and exit
    if (deleteNode != null)
    {
      for (index = deleteNode.height() - 1; index >= 0; index--)
      {
        currentNode = headNode;

        // If head pointer is equal to null, drop a level
        if (currentNode.pointerList.get(index) == null)
        {
          continue;
        }

        // If current nodes value is greater than our delete, drop a level
        else if (currentNode.pointerList.get(index).data.compareTo(data) > 0)
        {
          continue;
        }

        // If current points to our deleteNode, link current to the next node
        else if (currentNode.pointerList.get(index) == deleteNode)
        {
          currentNode.pointerList.set(index, deleteNode.pointerList.get(index));
        }

        // Loop through the list on this level till we find our delete node
        else
        {
          while (currentNode.pointerList.get(index) != deleteNode &&
                                                        currentNode.pointerList.get(index) != null)
          {
            currentNode = currentNode.pointerList.get(index);
          }

          // Link current to the next node
          currentNode.pointerList.set(index, deleteNode.pointerList.get(index));
        }
      }

      // Decerement the size and trim the height if necessary
      size--;
      if (getMaxHeightTrim(this.size()) < headNode.pointerList.size())
        trimSkipList(getMaxHeightTrim(this.size()));
    }
  }

  public static double difficultyRating()
  {
    return 5.0;
  }

  public static double hoursSpent()
  {
    return 20.0;
  }

  // Helper Methods

  //Returns the max height when we DO NOT want the head height to dicate max height (when deleting)
  private int getMaxHeightTrim(int n)
  {
    // Base conversion to find the max height given the number of nodes
    int logHeight = (int) Math.ceil(Math.log(n) / Math.log(2));

    // Prevents nodes with a height of 0
    if (n == 0 || n == 1)
      return 1;

    return logHeight;
  }

  // Returns the max height when we DO want the head height to dicate max height
  private int getMaxHeight(int n)
  {
    // Base conversion to find the max height given the number of nodes
    int logHeight = (int) Math.ceil(Math.log(n) / Math.log(2));
    int headHeight = headNode.pointerList.size();

    // Prevents nodes with a height of 0
    if (n == 0)
      return 1;

    return (headHeight > logHeight) ? headHeight : logHeight;
  }

  private static int generateRandomHeight(int maxHeight)
  {
    // Generates a random height using repeated 50% chance to return the given level
    // Allows for 1/2 of height 1, 1/4 of height 2, 1/8 of height 3, etc.
    for (int i = 1; i < maxHeight; i++)
    {
      if(Math.random() <= 0.5)
      {
        return i;
      }
    }
    return maxHeight;
  }

  // Grows the head and allows each max height node a 50% chance to grow as well
  private void growSkipList()
  {
    int heightIndex = headNode.height() - 1;
    Node<AnyType> currentNode = headNode.pointerList.get(heightIndex);
    Node<AnyType> lastNode = headNode;

    headNode.grow();

    // Loops through all max height nodes
    while (currentNode != null)
    {
      if (currentNode.maybeGrow())
      {
        lastNode.pointerList.set(heightIndex + 1, currentNode);
        lastNode = currentNode;
      }
      currentNode = currentNode.pointerList.get(heightIndex);
    }
  }

  private void trimSkipList(int newHeight)
  {
    int index = headNode.height() - 1;
    Node<AnyType> currentNode = headNode;
    Node<AnyType> lastNode = headNode;

    // Loop until our head node has been trimmed to the new max height
    while (headNode.height() > newHeight)
    {
      currentNode = headNode;
      lastNode = headNode;

      // Trim the head, accounting for a head height greater than current max height
      while (currentNode.pointerList.get(index) == null && currentNode.height() > newHeight + 1)
      {
        currentNode.trim();
        index--;
      }

      // Loop accros the top of the list, trimming each max height node
      while (currentNode.pointerList.get(index) != null)
      {
        currentNode = currentNode.pointerList.get(index);
        lastNode.trim();
        lastNode = currentNode;
      }

      // A catch to ensure we trim the last max height node in the sequence
      if (currentNode != null && currentNode.height() > newHeight)
        currentNode.trim();

      index--;
    }
  }
}

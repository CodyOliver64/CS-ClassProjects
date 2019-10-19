// Cody Oliver
// COP 3503, Fall 2019

// ====================
// GenericBST: BST.java (updated)
// ====================
// Basic binary search tree (BST) implementation that supports insert() and
// delete() operations. This framework was provide for me to modify as part of
// Programming Assignment #2. It has been modified to be used with any Comparable object.
// Solution derived from webcourse notes and lab


import java.io.*;
import java.util.*;

// Node class that can take data of different types
class Node<T>
{
	T data;
	Node<T> left, right;

	Node(T data)
	{
		this.data = data;
	}
}

public class GenericBST<AnyType extends Comparable<AnyType>>
{
	private Node<AnyType> root;

	public void insert(AnyType data)
	{
		root = insert(root, data);
	}

	// Inserts a new node given a root and data of AnyType
	private Node<AnyType> insert(Node<AnyType> root, AnyType data)
	{
		// If root is null return the new node as the root
		if (root == null)
		{
			return new Node<>(data);
		}
		// Compare new data to see if it's less than or greater than our current node. Recursively call insert
		else if (data.compareTo(root.data) < 0)
		{
			root.left = insert(root.left, data);
		}
		else if (data.compareTo(root.data) > 0)
		{
			root.right = insert(root.right, data);
		}

		return root;
	}

	public void delete(AnyType data)
	{
		root = delete(root, data);
	}

	// Delete a node from the tree
	private Node<AnyType> delete(Node<AnyType> root, AnyType data)
	{
		// Tree is empty
		if (root == null)
		{
			return null;
		}

		// Search left or right in the tree given its comparable value
		else if (data.compareTo(root.data) < 0)
		{
			root.left = delete(root.left, data);
		}
		else if (data.compareTo(root.data) > 0)
		{
			root.right = delete(root.right, data);
		}
		else
		{
			// Delete if No Children
			if (root.left == null && root.right == null)
			{
				return null;
			}

			// Delete if 1 Child right
			else if (root.left == null)
			{
				return root.right;
			}

			// Delete if 1 Child left
			else if (root.right == null)
			{
				return root.left;
			}

			// Delete if 2 Children
			else
			{
				root.data = findMax(root.left);
				root.left = delete(root.left, root.data);
			}
		}

		return root;
	}

	// This method assumes root is non-null, since this is only called by
	// delete() on the left subtree, and only when that subtree is not empty.

	// Return the data that hold the highest comparable value
	private AnyType findMax(Node<AnyType> root)
	{

		// Loop until we find the right-most node, which will contain the high value object
		while (root.right != null)
		{
			root = root.right;
		}

		return root.data;
	}

	public boolean contains(AnyType data)
	{
		return contains(root, data);
	}

	// Check if our tree contains the given data
	private boolean contains(Node<AnyType> root, AnyType data)
	{

		// Tree is empty or we've reached a leaf node, tree can't contain the data
		if (root == null)
		{
			return false;
		}

		// Data is less than our current root, search the left subtree
		else if (data.compareTo(root.data) < 0)
		{
			return contains(root.left, data);
		}

		// Data is greater than our current root, search the right subtree
		else if (data.compareTo(root.data) > 0)
		{
			return contains(root.right, data);
		}

		// Data is equal to our current node
		else
		{
			return true;
		}
	}

	// Recursively print In order (left, middle, right)
	public void inorder()
	{
		System.out.print("In-order Traversal:");
		inorder(root);
		System.out.println();
	}

	private void inorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		inorder(root.left);
		System.out.print(" " + root.data);
		inorder(root.right);
	}

	// Recursively print Pre order (middle, left, right)
	public void preorder()
	{
		System.out.print("Pre-order Traversal:");
		preorder(root);
		System.out.println();
	}

	private void preorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		System.out.print(" " + root.data);
		preorder(root.left);
		preorder(root.right);
	}

	// Recursively print Post order (let, right, middle)
	public void postorder()
	{
		System.out.print("Post-order Traversal:");
		postorder(root);
		System.out.println();
	}

	private void postorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		postorder(root.left);
		postorder(root.right);
		System.out.print(" " + root.data);
	}

	/*public static void main(String [] args)
	{
		GenericBST<Integer> myTree = new GenericBST<>();

		for (int i = 0; i < 5; i++)
		{

			// Insert random numbers into the tree
			int r = (int)(Math.random() * 100) + 1;
			System.out.println("Inserting " + r + "...");
			myTree.insert(r);
		}

		// Print the tree using the three traversals
		myTree.inorder();
		myTree.preorder();
		myTree.postorder();
	}
	*/
	public static double difficultyRating()
	{
		return 3.0;
	}

	public static double hoursSpent()
	{
		return 3.0;
	}
}

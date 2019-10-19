// Cody Oliver
// COP 3503, Fall 2019
// UCF ID 3125452
// Project 3 - SneakyKnights

import java.io.*;
import java.util.*;
import java.awt.*;


public class SneakyKnights
{
  // Determines if any of the given Knights can attack each other (true if all are safe)
  public static boolean allTheKnightsAreSafe(ArrayList<String> coordinateStrings, int boardSize)
  {

    // HashSet to hold our unique coordinate Points
    HashSet<Point> currentKnights = new HashSet<Point>();

    // Arrays to represent movement options for each knights
    int [] columnOptions = {2, 2, -2, -2, 1, 1, -1, -1};
    int [] rowOptions = {1, -1, 1, -1, 2, -2, 2, -2};

    // Loop through each argument passed
    for (int i = 0; i < coordinateStrings.size(); i++)
    {
      String workerString = coordinateStrings.get(i);

      // Split strings between letters and numbers
      int splitPoint = getSplitPoint(workerString);
      String colString = workerString.substring(0, splitPoint);
      String rowString = workerString.substring(splitPoint);

      // Calculate index based on board position
      int colNumber = convertLettersToRow(colString);
      int rowNumber = Integer.parseInt(rowString);

      // Convert each coordinate pair into a Point object, add it to the HashSet
      Point currentPosition = new Point(colNumber, rowNumber);
      currentKnights.add(currentPosition);

      // a loop to simulate all potential movements of a Knight
      for (int j = 0; j < columnOptions.length; j++)
      {
        // Point object to represent each potential attack position
        Point possibleAttack = new Point(colNumber + columnOptions[j], rowNumber + rowOptions[j]);

        if (currentKnights.contains(possibleAttack))
          return false;
      }
    }
    // getting through the for loop means all queens are safe
    return true;
  }


  public static int getSplitPoint(String stringy)
  {
    // scan string for index of first number
    for (int i = 0; i < stringy.length(); i++)
    {
      if (stringy.charAt(i) < 'a')
        return i;
    }
    // error if no index is found
    return -1;
  }

  // base 26 conversion
  public static int convertLettersToRow(String letterString)
  {
    int sum = 0;

    // loop through each letter
    for (int i = 0; i < letterString.length(); i++)
    {
      // powers of 26
      sum = sum * 26;
      // based on ASCII value
      sum = sum + (letterString.charAt(i) - 'a' + 1);
    }
    return sum;
  }

  public static double difficultyRating()
  {
    return 4.0;
  }

  public static double hoursSpent()
  {
    return 12.0;
  }
}

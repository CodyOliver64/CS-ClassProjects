// Cody Oliver
// COP 3503, Fall 2019
// UCF ID 3125452
// Project 1 - SneakyQueens

import java.io.*;
import java.util.*;

public class SneakyQueens
{
  public static boolean allTheQueensAreSafe(ArrayList<String> coordinateStrings, int boardSize)
  {
    // arrays to store frequency of each index of the board based on queen movement
    int[] colFrequency = new int[boardSize];
    int[] rowFrequency = new int[boardSize];
    int[] leftDiagFrequency = new int[boardSize + boardSize];
    int[] rightDiagFrequency = new int[boardSize + boardSize];


    // loop through each argument passed
    for (int i = 0; i < coordinateStrings.size(); i++)
    {
      String workerString = coordinateStrings.get(i);

      // split strings between letters and numbers
      int splitPoint = getSplitPoint(workerString);
      String colString = workerString.substring(0, splitPoint);
      String rowString = workerString.substring(splitPoint);

      // calculate index based on board position
      int colNumber = convertLettersToRow(colString) - 1;
      int rowNumber = Integer.parseInt(rowString) - 1;
      int leftDiagNumber = colNumber + rowNumber;
      int rightDiagNumber = (rowNumber - colNumber) + boardSize;

      // evaluate row
      if (colFrequency[colNumber] >= 1)
        return false;
      else
        colFrequency[colNumber]++;

      // evaluate column
      if (rowFrequency[rowNumber] >= 1)
        return false;
      else
        rowFrequency[rowNumber]++;

      // evaluate left diagonal
      if (leftDiagFrequency[leftDiagNumber] >= 1)
        return false;
      else
        leftDiagFrequency[leftDiagNumber]++;

      // evaluate right diagonal
      if (rightDiagFrequency[rightDiagNumber] >= 1)
        return false;
      else
        rightDiagFrequency[rightDiagNumber]++;
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
    return 8.0;
  }
}

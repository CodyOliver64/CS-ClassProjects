/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package userinterface;

import constants.Constants;
import core.Game;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;

/**
 *
 * @author Cody Oliver (derived from Webcourse Solution)
 */
public class MasterMindUi 
{
    private Game game;
    private CodebreakerUi codebreakerUi;
    private CodemakerUi codemakerUi;
    
    private JFrame frame;
    private JMenuBar menuBar;
    private JMenu gameMenu;
    private JMenu helpMenu;
    private JMenuItem newGameMenuItem;
    private JMenuItem exitMenuItem;
    private JMenuItem aboutMenuItem;
    private JMenuItem rulesMenuItem;
    
    public MasterMindUi(Game game)
    {
        this.game = game;
        initComponents();
        play();
    }
    
    public void play()
    {
        int tcount;
        //loop for the 10 tries allowed for guessing
        for(tcount = (Constants.MAX_ATTEMPTS - 1); tcount >= 0; tcount--)
        {
            //remove option to click check button
            codemakerUi.getCheck().setEnabled(false);
            codemakerUi.setCheckClicked(false);
            
            JOptionPane.showMessageDialog(frame, 
                                               "Codebreaker, enter your guess");
            
            //pause while they enter their guess
            while(game.getCodebreaker().getCodebreakerAttempt().size() != 4)
            {
                System.out.println("");
                continue;
            }
            
            //enable chekc button once ready
            codemakerUi.getCheck().setEnabled(true);
            JOptionPane.showMessageDialog(frame, 
                                        "Codebreaker, click the check button");
            
            while(!codemakerUi.isCheckClicked())
            {
                System.out.println("");
                continue;
            }
            
            if(codemakerUi.isCheckClicked())
            {
               JOptionPane.showMessageDialog(frame, 
                                        "Codemaker checking attempt");
               
               ArrayList<Color> guess = game.getCodebreaker().
                                                        getCodebreakerAttempt();
               game.getCodemaker().checkAttemptedCode(guess);
               
               ArrayList<Color> response = game.getCodemaker().
                                                        getCodemakerResponse();
               codemakerUi.displayCodemakerResponse(tcount);
            }
            
            //remove old guess
            game.getCodebreaker().removeAll();
            
            //win condition
            if(game.getCodemaker().isCodeGuessed())
            {
               JOptionPane.showMessageDialog(frame, 
                                        "Congratulations, You won!"); 
               codemakerUi.displaySecretCode();
               break;
            }
        }
        
        //loss condition
        if(!game.getCodemaker().isCodeGuessed())
        {
            System.out.println("last turn, not guessed");
            JOptionPane.showMessageDialog(frame, 
                                        "Sorry! You lost!");
            codemakerUi.displaySecretCode();
        }
    }
    
    private void initComponents()
    {
        // instantiate the codebreaker and codemaker UIs
        codebreakerUi = new CodebreakerUi(game.getCodebreaker());
        codemakerUi = new CodemakerUi(game.getCodemaker());
        
        // create the jframe
        frame = new JFrame("Mastermind");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 650);
        
        // create the jmenubar
        initMenuBar();
        
        // add codebreaker UI components
        frame.add(codebreakerUi.getCodebreakerColors(), BorderLayout.SOUTH);
        frame.add(codebreakerUi.getCodebreakerAttempt(), BorderLayout.CENTER);
        
        // add codemaker UI components
        frame.add(codemakerUi.getSecretCode(), BorderLayout.NORTH);
        frame.add(codemakerUi.getCodemakerResponse(), BorderLayout.EAST);
        
        frame.setJMenuBar(menuBar);
        frame.setVisible(true);
    }
    
    private void initMenuBar()
    {
        menuBar = new JMenuBar();
        
        // game menu
        gameMenu = new JMenu("Game");
        newGameMenuItem = new JMenuItem("New Game");
        exitMenuItem = new JMenuItem("Exit");
        exitMenuItem.addActionListener(new ExitListener());
        
        // help menu
        helpMenu = new JMenu("Help");
        aboutMenuItem = new JMenuItem("About");
        aboutMenuItem.addActionListener(new AboutListener());   
        rulesMenuItem = new JMenuItem("Game Rules");
        // register action listener 
        rulesMenuItem.addActionListener(new RulesListener()); 

        // put it all together
        gameMenu.add(newGameMenuItem);
        gameMenu.add(exitMenuItem);
        
        helpMenu.add(aboutMenuItem);
        helpMenu.add(rulesMenuItem);
        
        menuBar.add(gameMenu);
        menuBar.add(helpMenu);
    }
   
    // inner classes
    
    private class ExitListener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent ae) 
        {
            int response = JOptionPane.showConfirmDialog(frame, "Confirm to exit Mastermind?", 
                    "Exit?", JOptionPane.YES_NO_OPTION);
            
            if (response == JOptionPane.YES_OPTION)
                System.exit(0);	        
        }
    }
    
    private class AboutListener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent ae) 
        {
            String message = "Mastermind version 1.0\nKarin Whiting\nSummer 2019";
            JOptionPane.showMessageDialog(frame, message);
        }
    }
    
    private class RulesListener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent ae) 
        {
            String stepOne = "Step 1: The codemaker selects a four color secret code, in any order, no duplicate colors.\n\n";
            String stepTwo = "Step 2: The codebreaker places a guess in the bottom row, no duplicate colors.\n\n";
            String stepThree = "Step 3: The codemaker gives feedback next to each guess row with four pegs\n" +
                               "~ Each red peg means that one of the guessed colors is correct, and is in the right location.\n" +
                               "~ Each white peg means that one of the guessed colors is correct, but is in the wrong location.\n\n";
            String stepFour = "Step 4: Repeat with the next row, unless the secret code was guessed on the first turn\n\n";
            String stepFive = "Step 5: Continue until the secret code is guessed or there are no more guesses left, there are 10 attempts\n";
            
            JOptionPane.showMessageDialog(frame, stepOne + stepTwo + stepThree + stepFour + stepFive);
        }
    }
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package userinterface;

import constants.Constants;
import core.Codemaker;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EtchedBorder;

/**
 *
 * @author Cody Oliver (derived from Webcourse Solution)
 */
public class CodemakerUi 
{
    private JPanel codemakerResponse;
    private JPanel secretCode;
    private JLabel[] secretLabels;
    private JLabel[][] responseLabels;
    private ImageIcon question;
    private JButton check;    
    private Codemaker codemaker;
    private boolean checkClicked;

    public JButton getCheck() {
        return check;
    }

    public void setCheck(JButton check) {
        this.check = check;
    }

    public boolean isCheckClicked() {
        return checkClicked;
    }

    public void setCheckClicked(boolean checkClicked) {
        this.checkClicked = checkClicked;
    }
    
    public CodemakerUi(Codemaker codemaker)
    {
        this.codemaker = codemaker;
        initComponents();
    }
    
    private void initComponents()
    {
        initCodemakerResponse();
        initSecretCode();
    }
    
    private void initCodemakerResponse()
    {
        codemakerResponse = new JPanel();
        codemakerResponse.setBorder(BorderFactory.createTitledBorder("Codemaker Response"));
        codemakerResponse.setMinimumSize(new Dimension(150, 100));
        codemakerResponse.setPreferredSize(new Dimension(150,100));
        codemakerResponse.setLayout(new GridLayout(Constants.MAX_ATTEMPTS, Constants.MAX_PEGS));
        
        // instantiate the Array with the size
        responseLabels = new JLabel[Constants.MAX_ATTEMPTS][Constants.MAX_PEGS];
        
        // create the array of JLabels for the code maker's response
        for (int row = 0; row < Constants.MAX_ATTEMPTS; row ++) 
        {			
            for(int col = 0; col < Constants.MAX_PEGS; col++)
            {
                // create the buttons
                responseLabels[row][col] = new JLabel();
                responseLabels[row][col].setOpaque(true);
                responseLabels[row][col].setBackground(Color.DARK_GRAY);
                responseLabels[row][col].setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));

                // add the button to the UI
                codemakerResponse.add(responseLabels[row][col]);
            }
        }
    }
    
    private void initSecretCode()
    {
        secretCode = new JPanel();
        secretCode.setBorder(BorderFactory.createTitledBorder("Secret Code"));
        secretCode.setMinimumSize(new Dimension(200, 60));
        secretCode.setPreferredSize(new Dimension(200,60));
        secretCode.setAlignmentY(JPanel.TOP_ALIGNMENT);
        
        // instantiate the Array with the size
        secretLabels = new JLabel[Constants.MAX_PEGS];
        
//        question = new ImageIcon( getClass().getResource("../images/question.jpg"));

        String fileName = "../images/question.jpg";
        URL imgURL = getClass().getResource(fileName);
        
        if(imgURL != null)
        {
            question = new ImageIcon(imgURL);
            question = imageResize(question);
        }
        else
        {
            System.err.println("Couldn't find file: " + fileName);
            question = null;
        }
        
        // counter for enhanced for loop
        int counter = 0;
        
        for (JLabel label : secretLabels) 
        {			
            label = new JLabel();
            label.setBackground(Color.LIGHT_GRAY);
            label.setIcon(imageResize(question));
            
            // add button to JPanel using FlowLayout
            secretCode.add(label);
            
            // increment the counter
            counter++;
        }
        
        // ghetto spacing
        JLabel space = new JLabel();
        space.setMinimumSize(new Dimension(100, 35));
        space.setPreferredSize(new Dimension(100, 35));
        secretCode.add(space);
        
        // add the check button
        check = new JButton("Check");
        check.addActionListener(new CheckListener());
        secretCode.add(check);
    }

    public void displaySecretCode()
    {
        int i;
        secretCode.removeAll();
        
        JLabel code = new JLabel("The secret code was ");
        secretCode.add(code);
        
        List<Color> secretList = new ArrayList<Color>(codemaker.getSecretCode());
        
        for(i=0; i<codemaker.getSecretCode().size(); i++)
        {
          Color color = secretList.get(i);
          RoundButton elButton = new RoundButton();
          elButton.setMinimumSize(new Dimension(30,30));
          elButton.setPreferredSize(new Dimension(30,30));
          elButton.setMaximumSize(new Dimension(30,30));
          elButton.setBackground(color);
          secretCode.add(elButton);
        }
        
        secretCode.revalidate();
        secretCode.repaint();
    }
    
    public void displayCodemakerResponse(int row)
    {
        ArrayList<Color> response = codemaker.getCodemakerResponse();
        
        for(int col = 0; col < response.size(); col++)
        {
            Color color = response.get(col);
            if(color != null)
            {
                responseLabels[row][col].setOpaque(true);
                responseLabels[row][col].setBackground(color);
            }
        }
        response.removeAll(response);
    }
    
    private class CheckListener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent ae)
        {
            checkClicked = true;
        }
    }
    
    /**
     * @return the codemakerResponse
     */
    public JPanel getCodemakerResponse() 
    {
        return codemakerResponse;
    }

    /**
     * @return the secretCode
     */
    public JPanel getSecretCode() 
    {
        return secretCode;
    }
    
    private ImageIcon imageResize(ImageIcon icon)
    {
        Image image = icon.getImage();
        Image newImage = image.getScaledInstance(30, 30, java.awt.Image.SCALE_SMOOTH);
        icon = new ImageIcon(newImage);
        return icon;
    }
}

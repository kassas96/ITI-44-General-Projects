/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package mini_project_kassas_huda_v2;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;


/**
 *
 * @author kassas
 */
public class Buttons extends JPanel {

    //colors buttons
    JButton redButton;
    JButton greenButton;
    JButton blueButton;
    JButton yellowButton;
    JButton pinkButton;
    JButton cyanButton;
    JButton magentaButton;
    JButton blackButton;
    JButton whiteButton;
    JButton grayButton;
    
  
   
    //drop down menu for style
     JComboBox <String> stoke_style; 
//drop down menu for stroke size
     JComboBox <Integer> stoke_size; 
//drop down menu for background color
     JComboBox <String> background_color;  
     
//Check box for filled shape or not     
     JCheckBox filledButton;
//Titles
     JLabel size_title ;
     JLabel style_title;
     JLabel back_title ;
     
    
    public Buttons() {

            
//Objects (color buttons) created from Button class.
        
        redButton = new JButton();
        greenButton = new JButton();
        blueButton = new JButton();
        yellowButton = new JButton();
        pinkButton = new JButton();
        cyanButton = new JButton();
        magentaButton = new JButton();
        blackButton = new JButton();
        whiteButton = new JButton();
        grayButton = new JButton();
               
//set a color on the bottons
        redButton.setBackground(Color.RED);
        greenButton.setBackground(Color.GREEN);
        blueButton.setBackground(Color.BLUE);
        yellowButton.setBackground(Color.YELLOW);
        pinkButton.setBackground(Color.PINK);
        cyanButton.setBackground(Color.CYAN);
        magentaButton.setBackground(Color.MAGENTA);
        blackButton.setBackground(Color.BLACK);
        whiteButton.setBackground(Color.WHITE);
        grayButton.setBackground(Color.GRAY);
        
        //adding color buttons to my panel
        add(redButton);
        add(blueButton);
        add(greenButton);
        add(yellowButton);
        add(pinkButton);
        add(cyanButton);
        add(magentaButton);
        add(whiteButton);
        add(blackButton);
        add(grayButton); 
        
     
//set position of the bottons        
       // redButton.setBounds(10, 5, 2, 2);

//create a check box for filled shapes or not
        filledButton = new JCheckBox("Fill Object", Paint_Brush_Panel.states);
        
        
                 
// Create drop down menu 

         stoke_size = new JComboBox <>(new Integer[]{1,2,3,4,5,6});
         stoke_style= new JComboBox <>(new String []{"Solid","Dashed","Dotted"});
         background_color = new JComboBox <>(new String []{"White","Black"});
         
 // Create Labels for the drop down menu        
           size_title =new JLabel("Stroke Size");
           style_title =new JLabel("Stroke Style");
           back_title =new JLabel("background");
         
//================================================================================================= 
//ADDING THE BUTTONS ON THE PANEL
//================================================================================================= 


        

//adding filled check box to my panel
        add(filledButton, BorderLayout.NORTH);
        
//adding drop down menu to my panel 
         add(style_title);
        add(stoke_style, BorderLayout.WEST);
        add(size_title);
        add(stoke_size, BorderLayout.WEST);
        add(back_title);
        add(background_color, BorderLayout.WEST);
          
        
        //================================================================================================= 
//Listeners Implementation
//================================================================================================= 

//Implementing Action listeners for each color button
            redButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e){
               Paint_Brush_Panel.colors=1;
              //  updateUI();
            }
            
        });


            

           greenButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
               Paint_Brush_Panel.colors=2;
              //  updateUI();
               }
            
        });
            
            blueButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
                Paint_Brush_Panel.colors=3;
               // updateUI();
               }
            
        }); 
            
             yellowButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
                Paint_Brush_Panel.colors=4;
               // updateUI();
               }
            
        });
             
              pinkButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
                Paint_Brush_Panel.colors=5;
              //  updateUI();
               }
            
        }); 
              
               cyanButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
                Paint_Brush_Panel.colors=6;
               // updateUI();
               }
            
        }); 
               
                magentaButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
                Paint_Brush_Panel.colors=7;
              //  updateUI();
               }
            
        });  
                
                blackButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
                Paint_Brush_Panel.colors=8;
                //updateUI();
               }
            
        });  
                
                whiteButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
                Paint_Brush_Panel.colors=9;
              //  updateUI();
               }
            
        });  
                
                grayButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
                Paint_Brush_Panel.colors=10;
              //  updateUI();
               }
            
        }); 
                
                
//Implementing item listeners for the check box
         filledButton.addItemListener(new ItemListener() {

            @Override
            public void itemStateChanged(ItemEvent e) {
                Paint_Brush_Panel.states = filledButton.isSelected();}
        });

 //=================================================================================================
 
 //Implementing item listeners for the stroke size drop down menu        
         stoke_size.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
               
                Paint_Brush_Panel.size= (int) stoke_size.getSelectedItem();
               // repaint();
            }
        });

 //Implementing item listeners for the stroke style drop down menu        
         stoke_style.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
               
                
               switch((String)stoke_style.getSelectedItem()){
                   case "Solid":
                      Paint_Brush_Panel.style=1;
                      break;
                    case "Dashed":
                      Paint_Brush_Panel.style=2;
                      break;
                    case "Dotted":
                      Paint_Brush_Panel.style=3;
                      break; 
                    default:
                       Paint_Brush_Panel.style=1;
                      break; 
               } 
                
             //  repaint();
            }
        });

         
//Implementing item listeners for the background color drop down menu        
         background_color.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
               
                 switch((String)background_color.getSelectedItem()){
                   case "White":
                      Paint_Brush_Panel.back_color=9;
                      Paint_Brush_Panel.shape_Arr.clear();
                      break;
                    case "Black":
                      Paint_Brush_Panel.back_color=8;
                      Paint_Brush_Panel.shape_Arr.clear();
                      break;
                    
                    default:
                       Paint_Brush_Panel.back_color=9;
                      break; 
               } 
               
                repaint();
            }
        });         
         
  
          

    }
     @Override
        protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;
        
//setting the postion of the buttons
         redButton.setBounds(10, 10, 30, 30);
          greenButton.setBounds(50, 10, 30, 30);
           blueButton.setBounds(10, 50, 30, 30);
            yellowButton.setBounds(50, 50, 30, 30);
             pinkButton.setBounds(10, 100, 30, 30);
              cyanButton.setBounds(50, 100, 30, 30);
               magentaButton.setBounds(10, 150, 30, 30);
                blackButton.setBounds(50, 150, 30, 30);
                 whiteButton.setBounds(10, 200, 30, 30);
                  grayButton.setBounds(50, 200, 30, 30);
                  
               
            filledButton.setBounds(5, 250, 90, 25);
            back_title.setBounds(5, 290, 100, 25);
            background_color.setBounds(5, 310, 60, 25); 
            style_title.setBounds(5, 370, 100, 25);
            stoke_style.setBounds(5, 390, 70, 25); 
            size_title.setBounds(5, 470, 100, 25);
            stoke_size.setBounds(15, 490, 35, 25);        
                   
     
        }
    
    
}

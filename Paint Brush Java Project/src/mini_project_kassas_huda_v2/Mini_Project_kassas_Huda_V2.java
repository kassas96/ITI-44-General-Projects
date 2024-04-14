/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package mini_project_kassas_huda_v2;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.*;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 * @author fatem
 */
public class Mini_Project_kassas_Huda_V2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
       JFrame frame = new JFrame();
        frame.setTitle("Paint Brush By Mohamed El_Kassas & Huda ");
        
         JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BorderLayout());

        Buttons b=new Buttons();
        b.setBackground(Color.lightGray);
        b.setPreferredSize(new Dimension(100, 0));
        
      
        
        Paint_Brush_Panel panel;
        try {
            panel = new Paint_Brush_Panel();
             panel.setBackground(Color.WHITE);
        
         
       
        
          // Add the left and right panels to the main panel
        mainPanel.add(b, BorderLayout.WEST);
        mainPanel.add(panel, BorderLayout.CENTER);

        frame.add(mainPanel);
        
        
        frame.setSize(1800, 800);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
       } catch (IOException ex) {
            Logger.getLogger(Mini_Project_kassas_Huda_V2.class.getName()).log(Level.SEVERE, null, ex);
        }
        
       

        
    }

    
    
}

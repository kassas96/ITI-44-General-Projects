
package mini_project_kassas_huda_v2;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
 *
 *  @Mohamed El_Kassas & Huda 
 */
public class Paint_Brush_Panel extends JPanel {
    
   private int x1, x2, y1, y2;
   private int shapes;
  public static int  colors;
   public static int size;
   public static int style;
   public static int back_color;
   public static  boolean states = false;
   private BufferedImage image; 
    
//Array list creation.
     public static List<Geoshape> shape_Arr;
      public static List<Geoshape> redo_Arr;
       
 //================================================================================================= 
    //Objects Declearation
 //================================================================================================= 
    
    
//popup menu for shapes type
   private JPopupMenu popupMenu;

    
    
//option buttons
    JButton clearAllButton;
    JButton undoButton;
    JButton redoButton;
    JButton eraseButton;
    JButton saveButton;
    JButton openButton;
    

    
//Objects reference creation.
    Oval oval;
    Rectangle rect;
    Line line;
    Point point;

   
 //================================================================================================= 
 //================================================================================================= 
    
  //Default constructor for Paint_Brush_Panel Class
    public Paint_Brush_Panel() throws IOException {
        
        
        this.setFocusable(true);

//================================================================================================= 
//Creating objects 
//================================================================================================= 
        
//creating the array of shapes
        shape_Arr = new ArrayList<>();
        redo_Arr = new ArrayList<>();
        
      
//Objects created from Object classes.
        oval = new Oval();
        rect = new Rectangle();
        line = new Line();
        point =new Point();
 
//Objects (options buttons) created from Button class.        
        clearAllButton = new JButton("Clear");
        undoButton = new JButton("Undo");
        redoButton = new JButton("Redo");
        eraseButton= new JButton("Erase");
        saveButton = new JButton("Save");
        openButton = new JButton("Open");
     
//set photo on the bottons        
    try{
// Load the image
            BufferedImage image2 = ImageIO.read(new File("..\\8373519.png"));
            BufferedImage image3 = ImageIO.read(new File("..\\eraser.jpg"));
            BufferedImage image4 = ImageIO.read(new File("..\\clear.jpeg"));
            BufferedImage image5 = ImageIO.read(new File("..\\save.jpg"));
            BufferedImage image6 = ImageIO.read(new File("..\\redo.png"));
         
// Resize the image
            int width = 30; 
            int height = 15; 
            Image resizedImage = image2.getScaledInstance(width, height, Image.SCALE_SMOOTH);
            Image resizedImage3 = image3.getScaledInstance(width, height, Image.SCALE_SMOOTH);
            Image resizedImage4 = image4.getScaledInstance(width, height, Image.SCALE_SMOOTH);
            Image resizedImage5 = image5.getScaledInstance(width, height, Image.SCALE_SMOOTH);
            Image resizedImage6 = image6.getScaledInstance(width, height, Image.SCALE_SMOOTH);

            
// Create an ImageIcon with the resized image
            ImageIcon icon = new ImageIcon(resizedImage);
            ImageIcon icon3 = new ImageIcon(resizedImage3);
             ImageIcon icon4 = new ImageIcon(resizedImage4);
             ImageIcon icon5 = new ImageIcon(resizedImage5);
             ImageIcon icon6 = new ImageIcon(resizedImage6);
             
        
// Set the ImageIcon as the button's icon
        undoButton.setIcon(icon);
        eraseButton.setIcon(icon3);
        clearAllButton.setIcon(icon4);
        saveButton.setIcon(icon5);
        redoButton.setIcon(icon6);
        
          } catch (IOException e) {
            e.printStackTrace();
        }


        
// Create popup menu items 
        popupMenu = new JPopupMenu();
        JMenuItem l = new JMenuItem("Line");
        JMenuItem rec = new JMenuItem("Rectangle");
        JMenuItem ov = new JMenuItem("Oval");
        JMenuItem free = new JMenuItem("Free Hand");
 
//================================================================================================= 
//ADDING THE BUTTONS ON THE PANEL
//================================================================================================= 

//adding option buttons to my panel
        add(clearAllButton);
        add(undoButton);
        add(redoButton);
        add(eraseButton);
        add(saveButton);
        add(openButton);        


// Add the items (shapes) in the popup menu   
         popupMenu.add(l);
         popupMenu.add(rec);
         popupMenu.add(ov);
         popupMenu.add(free);
    
     
// Attach the popup menu to the panel
        this.setComponentPopupMenu(popupMenu);
        
        
        
//================================================================================================= 
//Listeners Implementation
//================================================================================================= 


//=================================================================================================

//Implementing action listener for each shape in the popup menu
        l.addActionListener(new ActionListener(){
         
            @Override
            public void actionPerformed(ActionEvent e) {
            
                shapes=1;
       
            }
         });
        

        
        rec.addActionListener(new ActionListener(){
         
            @Override
            public void actionPerformed(ActionEvent e) 
            {
            
                shapes=2;
               
            }
         });
          
           ov.addActionListener(new ActionListener(){
         
            @Override
            public void actionPerformed(ActionEvent e) 
            {
            
                shapes=3;
               
            }
         });
           
           free.addActionListener(new ActionListener(){
         
            @Override
            public void actionPerformed(ActionEvent e) 
            {
            
                shapes=4;
               
            }
         });

//=================================================================================================

         
  //=================================================================================================        
 //Implementing listeners for the options buttons   
  //=================================================================================================  
         undoButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
                   
                   if (shape_Arr.size() > 0) {
                       
       //save the shape fo redo button
                    redo_Arr.add(shape_Arr.getLast());
      //removes the shape from the array list                
                    shape_Arr.remove(shape_Arr.size() - 1);
                    
                    
      //removes the shape from the drawing area by resetting its position             
                    switch (shapes) {
                        case 1:
                            line.setX1(0);
                            line.setY1(0);
                            line.setX2(0);
                            line.setY2(0);
                            
                            break;
                        case 2:
                            rect.setX1(0);
                            rect.setY1(0);
                            rect.setX2(0);
                            rect.setY2(0);
                            break;
                        case 3:
                            oval.setX1(0);
                            oval.setY1(0);
                            oval.setX2(0);
                            oval.setY2(0);
                            break;
                        case 4:
                            point.setX1(0);
                            point.setY1(0);
                            point.setX2(0);
                            point.setY2(0);
                            break; 
                         case 5:
                            point.setX1(0);
                            point.setY1(0);
                            point.setX2(0);
                            point.setY2(0);
                            break;    

                    }
                   
                 
                updateUI();
               }}
            
        }); 
//=================================================================================================          
          redoButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
                   
                   if (redo_Arr.size() > 0) {
      // Save the shape for undo button
            shape_Arr.add(redo_Arr.getLast());
      // Remove the shape from the redo array
            redo_Arr.remove(redo_Arr.size() - 1);
      // Update the UI to reflect the changes
            updateUI();
        }
               }
            
        }); 
//=================================================================================================           
         eraseButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
               shapes=5;
               size=30;
               colors=back_color;
                updateUI();
               }
            
        });  
//=================================================================================================           
          clearAllButton.addActionListener(new ActionListener(){
           
               @Override
               public void actionPerformed(ActionEvent e)
               {
               shape_Arr.clear();
               switch (shapes) {
                        case 1:
                            line.setX1(0);
                            line.setY1(0);
                            line.setX2(0);
                            line.setY2(0);
                            
                            break;
                        case 2:
                            rect.setX1(0);
                            rect.setY1(0);
                            rect.setX2(0);
                            rect.setY2(0);
                            break;
                        case 3:
                            oval.setX1(0);
                            oval.setY1(0);
                            oval.setX2(0);
                            oval.setY2(0);
                            break;
                        case 4:
                            point.setX1(0);
                            point.setY1(0);
                            point.setX2(0);
                            point.setY2(0);
                            break; 
                         case 5:
                            point.setX1(0);
                            point.setY1(0);
                            point.setX2(0);
                            point.setY2(0);
                            break;    

                    }
                updateUI();
               }
            
        });
          
  
//=================================================================================================            
          saveButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                BufferedImage image = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_ARGB);
                Graphics2D g2d = image.createGraphics();
                paint(g2d);
                g2d.dispose();

                 JFileChooser fileChooser = new JFileChooser();      
                 fileChooser.setFileFilter(new FileNameExtensionFilter("PNG Images", "png"));
                 int option = fileChooser.showSaveDialog(Paint_Brush_Panel.this);
                 if (option == JFileChooser.APPROVE_OPTION) {
                     File file = fileChooser.getSelectedFile();
                     String filePath = file.getAbsolutePath();
                     if (!filePath.toLowerCase().endsWith(".png")) {
                         file = new File(filePath + ".png");
                     }
                     
                     // Specify the crop region
                        int cropX = 0;
                        int cropY = 50;
                        int cropWidth = 1250;
                        int cropHeight = 700;

                        // Create a cropped image
                        BufferedImage croppedImage = image.getSubimage(cropX, cropY, cropWidth, cropHeight);
                     
                     try {
                         ImageIO.write(croppedImage, "png", file);
                     } catch (IOException ex) {
                         ex.printStackTrace();
                     }
                 }

            }
        });
         
   //=================================================================================================         
          
   openButton.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser();
            int option = fileChooser.showOpenDialog(this);
            if (option == JFileChooser.APPROVE_OPTION) {
                File file = fileChooser.getSelectedFile();
                try {
                    image = ImageIO.read(file);
                    repaint();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        });
          
  //=================================================================================================       
       
 //Implementing mouse listeners to draw shapes and save it         
 this.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {
              
 if (e.getButton() == MouseEvent.BUTTON3) {
     x1=x2=y1=y2=0;  
     return; // Ignore the event if right mouse button is pressed
    }
if (e.getButton() == MouseEvent.BUTTON1) {
        if (shapes==1) {
            x1 = e.getX();
                y1 = e.getY();
                x2 = e.getX();
                y2 = e.getY();
                line.setX1(x1);
                line.setY1(y1);
                line.setX2(x2);
                line.setY2(y2);
             
        }
        if (shapes==2) {
            x1 = e.getX();
                y1 = e.getY();
                x2 = e.getX();
                y2 = e.getY();
                rect.setX1(x1);
                rect.setY1(y1);
                rect.setX2(x2);
                rect.setY2(y2);
             
        }
        if (shapes==3) {
            x1 = e.getX();
                y1 = e.getY();
                x2 = e.getX();
                y2 = e.getY();
                oval.setX1(x1);
                oval.setY1(y1);
                oval.setX2(x2);
                oval.setY2(y2);
             
        }
         if (shapes==4) {
            x1 = e.getX();
                y1 = e.getY();
                x2 = e.getX();
                y2 = e.getY();
                point.setX1(x1);
                point.setY1(y1);
                point.setX2(x2);
                point.setY2(y2);
             
        }
        
            }
            }
            @Override
            public void mousePressed(MouseEvent e) {
              if (e.getButton() == MouseEvent.BUTTON3) {
        return; // Ignore the event if right mouse button is pressed
    }
                
                if (e.getButton() == MouseEvent.BUTTON1) {
                    // Left mouse button clicked
                   
                x1 = e.getX();
                y1 = e.getY();
                
                 switch (shapes) {
                case 1:
                    line.setX1(x1);
                    line.setY1(y1);
                    line.setX2(x1);
                    line.setY2(y1);
                    break;
                case 2:
                    rect.setX1(x1);
                    rect.setY1(y1);
                    rect.setX2(x1);
                    rect.setY2(y1);
                    break;
                case 3:
                    oval.setX1(x1);
                    oval.setY1(y1);
                    oval.setX2(x1);
                    oval.setY2(y1);
                    break;
                case 4:
                    point.setX1(x1);
                    point.setY1(y1);
                    point.setX2(x1);
                    point.setY2(y1);
                    break;
                case 5:
                    point.setX1(x1);
                    point.setY1(y1);
                    point.setX2(x1);
                    point.setY2(y1);
                    break;
            }
            repaint();
        }
                   
                }
            

            

            @Override
            public void mouseReleased(MouseEvent e) {
                if (e.getButton() == MouseEvent.BUTTON3) {
        return; // Ignore the event if right mouse button is pressed
    }
               if (e.getButton() == MouseEvent.BUTTON1) {
                
                x2 = e.getX();
                y2 = e.getY();
                     
                    //current_shape = new Geoshape(x1, y1, x2, y2);
                    switch(shapes){
                        case 1:
                          shape_Arr.add(new Line(x1, y1, x2, y2,colors,size,style,states)); 
                          break;
                          
                           case 2:
                          shape_Arr.add(new Rectangle(x1, y1, x2, y2,colors,size,style,states)); 
                          break;
                           case 3:
                          shape_Arr.add(new Oval(x1, y1, x2, y2,colors,size,style,states)); 
                          break;
                           case 4:
//                          shape_Arr.add(new Point(x1, y1, x2, y2,colors,size,style,states)); 
                            point.setX1(x2);
                            point.setY1(y2);
                          break;
                            case 5:
                         // shape_Arr.add(new Point(x1, y1, x2, y2,colors,size,style,states)); 
                                 point.setX1(x2);
                            point.setY1(y2);
                          break;
                           default:
                               shape_Arr.add(new Line(x1, y1, x2, y2,colors,size,style,states)); 
                          break;
                          
                    }
                    
                    
                    repaint();
                
            }}

            @Override
            public void mouseEntered(MouseEvent e) {
            }

            @Override
            public void mouseExited(MouseEvent e) {
            }
        });

        this.addMouseMotionListener(new MouseMotionListener() {
            @Override
            public void mouseDragged(MouseEvent e) {
               if (e.getButton() == MouseEvent.BUTTON3) {
        return; // Ignore the event if right mouse button is pressed
    }
                
                x2 = e.getX();
                y2 = e.getY();
                
                switch(shapes){
                        case 1:
                          line.setX2(x2);
                          line.setY2(y2);
                          break;
                          
                           case 2:
                         rect.setX2(x2);
                          rect.setY2(y2);
                          break;
                           case 3:
                          oval.setX2(x2);
                          oval.setY2(y2);
                          break;
                           case 4:
                          point.setX2(x2);
                          point.setY2(y2);
                          shape_Arr.add(new Point(x1, y1, x2, y2,colors,size,style,states));
                           x1 = e.getX();
                           y1 = e.getY();
                          break;
                          case 5:
                          point.setX2(x2);
                          point.setY2(y2);
                         shape_Arr.add(new Point(x1, y1, x2, y2,colors,size,style,states));
                           x1 = e.getX();
                           y1 = e.getY();
                          break;
            }
               repaint();
            }

            
            
            
            @Override
            public void mouseMoved(MouseEvent e) {
            }
        });
         
    
         
    }
    
//=================================================================================================
//pianting function
//=================================================================================================    
            
         @Override
        protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;
        
//Background color switching 
       switch(getBackGroundColor()){
        
            case 9:
        this.setBackground(Color.white);
        break;
        case 8:
        this.setBackground(Color.black);
        break;
        default:
            this.setBackground(Color.white);
            back_color=9;
        break;
        }
       
       
         if (image != null) {
            g2d.drawImage(image, 0, 0, getWidth(), getHeight(), this);
        }
       
  
       
//Redraw the whole shapes           
            for (int i = 0; i < shape_Arr.size(); i++) {
                shape_Arr.get(i).drawShape(g2d);
            }

               switch(shapes){
                   case 1:
                       line.setCurrentColor(colors);
                       line.setIsFilled(states);
                       line.setStrockSize(size);
                       line.setstrockStyle(style);
                       line.drawShape(g2d);
                       break;
                   case 2:
                       rect.setCurrentColor(colors);
                       rect.setIsFilled(states);
                       rect.setStrockSize(size);
                       rect.setstrockStyle(style);
                       rect.drawShape(g2d);
                       break;
                    case 3:
                       oval.setCurrentColor(colors);
                       oval.setIsFilled(states);
                       oval.setStrockSize(size);
                       oval.setstrockStyle(style);
                       oval.drawShape(g2d);
                       break;   
                    case 4:
                       point.setCurrentColor(colors);
                       point.setIsFilled(states);
                       point.setStrockSize(size);
                      // point.setstrockStyle(style);
                       point.drawShape(g2d);
                       break;  
                       
                       case 5:
                           switch(back_color){
                               case 9:
                                    point.setCurrentColor(9);
                                   break;
                                case 8:
                                    point.setCurrentColor(8);
                                   break; 
                                default:
                                    point.setCurrentColor(9);
                                    break;
                           }
                      //point.setCurrentColor(getBackground());
                       point.setIsFilled(states);
                       point.setStrockSize(size);
                      // point.setstrockStyle(style);
                       point.drawShape(g2d);
                       break;  
               }
            
          

    }    
    
    
   
    
//function to get the background from the drop down menu
    public final int  getBackGroundColor(){
        
        return back_color;
    } 
    
}

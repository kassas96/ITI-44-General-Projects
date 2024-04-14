

package mini_project_kassas_huda_v2;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;

/**
 *
 * @author Huda
 */
public class Line extends Geoshape
{
   
    
    public Line()
    {
    }
    
      public Line(int x1, int y1, int x2, int y2, int c, int size, int style, boolean fill) 
    {
        super(x1, y1, x2, y2, c, size, style,fill);
    }
    
    @Override
    public void drawShape(Graphics2D g2d) 
    {
       
        
// Specify the color of the stroke
        switch(getCurrentColor())
        {
            case 1:
                g2d.setColor(Color.RED);
                break;
            case 2:
                g2d.setColor(Color.GREEN);
                break;
            case 3:
                g2d.setColor(Color.BLUE);
                break;
            case 4:
                g2d.setColor(Color.YELLOW);
                break;
            case 5:
                g2d.setColor(Color.PINK);
                break;
            case 6:
                g2d.setColor(Color.CYAN);
                     break;
            case 7:
                g2d.setColor(Color.MAGENTA);
                     break;
                     
             case 8:
                g2d.setColor(Color.BLACK);
                     break;         
            case 9:
                g2d.setColor(Color.WHITE);
                     break;    
             case 10:
                g2d.setColor(Color.GRAY);
                     break;          
            default:
                g2d.setColor(Color.BLACK);
                break;
                
            
        }
        
        
//  set the size and style of the stroke
            BasicStroke stroke;
        
        switch(getstrockStyle())
        {
            
           

               case 1:// Specify the Solid pattern
                    stroke = new BasicStroke(getStrockSize());
                    break;
                case 2:// Specify the dash pattern
                    float[] dashPattern = {5, 5}; 
                    stroke = new BasicStroke(getStrockSize(), BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10, dashPattern, 0);
                    break;
                case 3:// Specify the dot pattern
                    float[] dotPattern = {1, 5}; 
                    stroke = new BasicStroke(getStrockSize(), BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10, dotPattern, 0);
                    break;
                
                default:
                  stroke = new BasicStroke(getStrockSize());// Specify the default to be Solid pattern
                    break;
            }

            g2d.setStroke(stroke);
           
        
       
//modify the coordinates to suit the needed input 
       g2d.drawLine(getX1(), getY1(), getX2(), getY2());
        
    }  
}

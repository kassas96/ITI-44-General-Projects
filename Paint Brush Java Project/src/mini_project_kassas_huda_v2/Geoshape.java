

package mini_project_kassas_huda_v2;

import java.awt.Graphics;
import java.awt.Graphics2D;

/**
 *
 * @Mohamed El_Kassas & Huda 
 */
public abstract class Geoshape {

    //shape attributes decleration
   private
    int x1;
    int x2;
    int y1;
    int y2;
  
   public
    int currentColor;
    int strockSize;
    int strockStyle;
    boolean fillState;
    
    //defining the constructors
    public Geoshape() {
    }
    
    public Geoshape(int x1,int y1,int x2,int y2,int c,int size,int style,boolean fill) {
        
        this.x1=x1;
        this.x2=x2;
        this.y1=y1;
        this.y2=y2;
        this.currentColor=c;
        this.fillState=fill;
         this.strockSize=size;
        this.strockStyle=style;
    }
    
    //coordinate setters
   public void setX1(int x1){
        this.x1=x1;
    }
   public void setX2(int x2){
        this.x2=x2;
    }
   public void setY1(int y1){
        this.y1=y1;
    }
   public void setY2(int y2){
        this.y2=y2;
    }
    
    //coordinate getters
    
   public int getX1(){
       return x1;
    }
    
   public int getX2(){
       return x2;
    }
   public int getY1(){
       return y1;
    }
   public int getY2(){
       return y2;
    }
     
    //color setter
    
   public void setCurrentColor(int color){
        this.currentColor=color;
    }
    
    //color getter
    
   public int getCurrentColor(){
        return currentColor;
    }
    
   // filled color shape settter
    
   public void setIsFilled(boolean filled){
        this.fillState=filled;
    }
    
     // filled color shape getter
   public  boolean getIsFilled(){
        return fillState ;
    }
    
    // strocke size  settter
    
   public void setStrockSize(int size){
        this.strockSize=size;
    }
    
     // strocke size  gettter
   public int getStrockSize(){
        return strockSize ;
    }
    
   // strocke style  settter
    
   public void setstrockStyle(int style){
        this.strockStyle=style;
    }
    
     // strocke style  gettter
   public int getstrockStyle(){
        return strockStyle ;
    } 
    
   //Draw function that will be override according the inherited shape 
    public abstract void drawShape(Graphics2D g2d);
    
}

import javax.swing.JFrame;
import javax.swing.JPanel;

import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Shape;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.ImageObserver;
import java.text.AttributedCharacterIterator;
import java.util.ArrayList;
import java.awt.Event;

public class game_of_life extends JFrame {
    RenderArea ra;
    private int i;
    
    public game_of_life() {
        super("Game of Life");
        this.setSize(1005, 1030);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
        this.setResizable(false);
        ra = new RenderArea();
        ra.setFocusable(true);
        ra.grabFocus();
        add(ra);

        ra.edit_mode = true;
        ra.running = true;
    }

    public void update() {
        ArrayList<ArrayList<Boolean>> entities = new ArrayList<ArrayList<Boolean>>();// = ra.entities;
        int size1 = ra.entities.size();
        int size2 = ra.entities.get(0).size();
        for(int i=0;i<size1;i++)
        {
            entities.add( new ArrayList<Boolean>());
            for(int j=0;j<size2;j++)
            {
                int alive = 0;
                
                if(ra.entities.get((size1+i-1)%size1).get((size2+j-1)%size2)) alive++;
                if(ra.entities.get((size1+i-1)%size1).get((size2+j)%size2)) alive++;
                if(ra.entities.get((size1+i-1)%size1).get((size2+j+1)%size2)) alive++;

                if(ra.entities.get((size1+i)%size1).get((size2+j-1)%size2)) alive++;
                if(ra.entities.get((size1+i)%size1).get((size2+j+1)%size2)) alive++;

                if(ra.entities.get((size1+i+1)%size1).get((size2+j-1)%size2)) alive++;
                if(ra.entities.get((size1+i+1)%size1).get((size2+j)%size2)) alive++;
                if(ra.entities.get((size1+i+1)%size1).get((size2+j+1)%size2)) alive++;
                


                /*for(int k=-1;i<2;k++)
                {
                    for(int l = -1; l < 2 ;l++)
                    {
                        if(!(k==0 && l == 0))
                        {
                            if(ra.entities.get((size1+i+k)%size1).get((size2+j+l)%size2)) alive++;
                        }
                    }
                }*/

                if(ra.entities.get(i).get(j))
                {
                    if(alive < 2 || alive > 3)
                    {
                        //ra.entities.get(i).set(j,false);
                        entities.get(i).add(false);
                    }
                    else
                    {
                        entities.get(i).add(true);
                    }
                }
                else
                {
                    if(alive == 3)
                    {
                        //ra.entities.get(i).set(j,true);
                        entities.get(i).add(true);
                    }
                    else
                    {
                        entities.get(i).add(false);
                    }
                }

            }
        }
        ra.entities = entities;

    }

    class RenderArea extends JPanel implements KeyListener {
        public ArrayList<ArrayList<Boolean>> entities;

        public int diff;
        public boolean edit_mode;
        public boolean running;
        public RenderArea() {
            super();
            setSize(1000, 1000);
            setVisible(true);
            setBackground(Color.WHITE);
            setForeground(Color.BLACK);
            setLocation(0, 0);

            diff = 20;
            

            this.addMouseListener((MouseListener) new MouseListener(){
            
                @Override
                public void mouseReleased(MouseEvent arg0) {
                    
                }
            
                @Override
                public void mousePressed(MouseEvent arg0) {
                    clicked(arg0);
                }
            
                @Override
                public void mouseExited(MouseEvent arg0) {
                    
                }
            
                @Override
                public void mouseEntered(MouseEvent arg0) {
                    
                }
            
                @Override
                public void mouseClicked(MouseEvent arg0) {
                    
                }
            }); 
            this.addKeyListener(this);
            entities = new ArrayList<ArrayList<Boolean>>();
            for(int i=0;i<1000/diff;i++)
            {
                entities.add(new ArrayList<Boolean>());
                for(int j=0;j<1000/diff;j++)
                {
                    entities.get(i).add(false);
                }
            }
            
        }

        void clicked(MouseEvent arg0)
        {
            System.out.println("Button "+(arg0.getButton()== 1 ? "Left" : "Right"));
            System.out.println("X:"+arg0.getX()/diff);
            System.out.println("Y:"+arg0.getY()/diff);
            if(edit_mode)
            {
                entities.get(arg0.getX()/diff).set(arg0.getY()/diff,!entities.get(arg0.getX()/diff).get((arg0.getY()/diff)));
                this.update(this.getGraphics());
            }
            
        }


        @Override
        public void keyTyped(KeyEvent e) {
            //System.out.println(e.getKeyChar());
        }
    
        @Override
        public void keyReleased(KeyEvent e) {
            System.out.println("Key pressed:"+e.getKeyChar());
            if(e.getKeyChar()=='e')
            {
                edit_mode = !edit_mode;
            }
            else if(e.getKeyChar()=='q')
            {
                this.running = false;
            }
            else if(e.getKeyChar()=='c')
            {
                if(edit_mode)
                {
                    for(int i=0;i<this.entities.size();i++)
                    {
                        for(int j=0;j<this.entities.get(1).size();j++)
                        {
                            this.entities.get(i).set(j,false);
                        }
                    }
                    this.update(this.getGraphics());
                }
                
            }

        }
    
        @Override
        public void keyPressed(KeyEvent e) {
            //System.out.println(e.getKeyChar());
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.clearRect(0, 0, 1000, 1000);
            for(int i=0;i<1000;i+=diff)
            {
                g.drawLine(i, 0, i, 1000);
            }
            for(int j=0;j<1000;j+=diff)
            {
                g.drawLine(0, j, 1000, j);
            }
            for(int i=0;i<1000;i+=diff)
            {
                for(int j=0;j<1000;j+=diff)
                {
                    if(entities.get(i/diff).get(j/diff))
                    {
                        g.setColor(Color.BLACK);
                    
                    }
                    else
                    {
                        g.setColor(Color.WHITE);
                    }
                    
                    g.fillRect(i+2, j+2, diff-3, diff-3);
                }
            }
        }

        

        private static final long serialVersionUID = 1L;
        
    }

    private static final long serialVersionUID = 1L;
    public static void main(String args[])
    {
        game_of_life gol = new game_of_life();
        while(gol.ra.running)
        {
            if(!gol.ra.edit_mode)gol.update();
            try{Thread.sleep(200);}
            catch(Exception ex)
            {

            }
            gol.ra.update(gol.ra.getGraphics());
        }
        gol.dispose();
    }
}

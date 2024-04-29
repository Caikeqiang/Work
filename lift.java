package elevator;

import java.awt.*;
import java.awt.event.*;

public class elevator {
    private Frame f;
    private Button butUp;
    private Button butDown;
    private Label lab1;
    private Label lab2;
    private TextField personFloor;
    private TextField personToFloor;
    private TextArea screen1;
    private TextArea screen2;
    private TextArea screen3;
    private TextArea screen4;

    private static int order;

    elevator() {
        order = 0;
        init();
        myRun();
    }

    public void init() {
        f = new Frame("Elevator dispatching");
        f.setSize(400, 400);
        f.setLayout(new FlowLayout());
        f.setResizable(false);
        f.setLocationRelativeTo(null);

        lab1 = new Label("当前楼层");
        lab2 = new Label("目的楼层");

        personFloor = new TextField("", 10);
        personToFloor = new TextField("", 10);

        butUp = new Button("↑");
        butDown = new Button("↓");

        screen1 = new TextArea("显示屏", 5, 10, TextArea.SCROLLBARS_NONE);
        screen2 = new TextArea("显示屏", 5, 10, TextArea.SCROLLBARS_NONE);
        screen3 = new TextArea("显示屏", 5, 10, TextArea.SCROLLBARS_NONE);
        screen4 = new TextArea("显示屏", 5, 10, TextArea.SCROLLBARS_NONE);

        screen1.setEditable(false);
        screen2.setEditable(false);
        screen3.setEditable(false);
        screen4.setEditable(false);

        f.add(lab1);
        f.add(personFloor);
        f.add(butUp);
        f.add(butDown);
        f.add(lab2);
        f.add(personToFloor);
        f.add(screen1);
        f.add(screen2);
        f.add(screen3);
        f.add(screen4);

        myEvent();

        f.setVisible(true);
    }

    public boolean isBetween20(int floor) {
        if (floor >= 0 && floor <= 20)
            return true;
        return false;
    }

    public boolean isCorrect(int order, int floor, int toFloor) {
        if (1 == order) {
            if (!isBetween20(floor)) {
                System.out.println("你在这？？      " + floor + "");
                return false;
            }
            if (!isBetween20(toFloor)) {
                System.out.println("你要去这？？   " + floor);
                return false;
            }
            if (toFloor <= floor) {
                System.out.println("你确定是要上楼？ 从  " + floor + "-> " + toFloor);
                return false;
            }
            return true;
        } else {
            if (!isBetween20(floor)) {
                System.out.println("你在这？？      " + floor + "");
                return false;
            }
            if (!isBetween20(toFloor)) {
                System.out.println("你要去这？？   " + floor);
                return false;
            }
            if (toFloor >= floor) {
                System.out.println("你确定是要下楼？ 从  " + floor + "-> " + toFloor);
                return false;
            }
            return true;
        }
     }

     public int whoIsRun(int e1Distance,int e2Distance,int e3Distance,int e4Distance){//根据传入参数判断哪个电梯最优
        int[] arr = new int[]{e1Distance,e2Distance,e3Distance,e4Distance};
        int index=0;
        for(int i=1;i<4;i++){
        	if(arr[index]>arr[i])
        		index = i;
        }
        return index+1;
     }

     private void myEvent(){//创建事件监听
        f.addWindowListener(new WindowAdapter(){
        	public void windowClosing(WindowEvent e){
        		System.exit(0);
        	}
        });

        personFloor.addKeyListener(new KeyAdapter(){
        	public void keyPressed(KeyEvent e){

        		int code = e.getKeyCode();
        		if(!(code>=KeyEvent.VK_0 && code <= KeyEvent.VK_9 || code==8))
        		{
        		       System.out.println(code+"... 是非法的");
        		       e.consume();
        		        }
        		    }
        		});

        personToFloor.addKeyListener(new KeyAdapter(){
        	public void keyPressed(KeyEvent e){
        	   int code = e.getKeyCode();
        	   if(!(code>=KeyEvent.VK_0 && code <= KeyEvent.VK_9 || code==8))
        	   {
        		            System.out.println(code+"... 是非法的");
        		            e.consume();
        		        }
        		    }
        	});

        butUp.addActionListener(new ActionListener(){//上升按钮
            public void actionPerformed(ActionEvent e){
        		        int personF = new Integer(personFloor.getText());
        		        int personTF = new Integer(personToFloor.getText());
        		        if(isCorrect(1,personF,personTF))
        		        {
        		            order = 1;
        		        }
        		        else
        		            order = 0;
        		        System.out.println("上升按钮按下");
        		    }
        	});

        butDown.addActionListener(new ActionListener(){//下降按钮
        	public void actionPerformed(ActionEvent e){
        		        int personF = new Integer(personFloor.getText());
        		        int personTF = new Integer(personToFloor.getText());
        		        if(isCorrect(-1,personF,personTF))
        		        {
        		            order = -1;
        		        }
        		        else
        		            order = 0;
        		        System.out.println("下降按钮按下");
        		    }
        		});
        }

        public void myRun()//为了调用非静态方法自创的主函数~
        {    

        		Elevator e1 = new Elevator(1,800,0);
        		Elevator e2 = new Elevator(2,800,1);
        		Elevator e3 = new Elevator(3,1600,2);
        		Elevator e4 = new Elevator(4,2000,0);
        		Controller controller1 = new Controller(e1);
        		Controller controller2 = new Controller(e2);
        		Controller controller3 = new Controller(e3);
        		Controller controller4 = new Controller(e4);

        		Thread t1 = new Thread(controller1);
        		Thread t2 = new Thread(controller2);
        		Thread t3 = new Thread(controller3);
        		Thread t4 = new Thread(controller4);
        		t1.start();
        		t2.start();
        		t3.start();
        		t4.start();
        		
        		while(true)//接收命令
        		{    
        		    try {
        		        Thread.sleep(2000);
        		    } catch (InterruptedException e) {
        		        e.printStackTrace();
        		    }

        		    //逻辑判断，哪个电梯拥有最短路径哪个电梯去接人
        		    if(1 == order){//上升按钮
        		        int personF = new Integer(personFloor.getText());
        		        int personTF = new Integer(personToFloor.getText());

        		        //逻辑判断 电梯最优方案
        		        int e1Distance = e1.countDistance(personF, order);
        		        int e2Distance = e2.countDistance(personF, order);
        		        int e3Distance = e3.countDistance(personF, order);
        		        int e4Distance = e4.countDistance(personF, order);
        		        int result = whoIsRun(e1Distance,e2Distance,e3Distance,e4Distance);
        		        switch(result){
        		            case 1:
        		                e1.add(personF, order, personTF);
        		                break;
        		            case 2:
        		                e2.add(personF, order, personTF);
        		                break;
        		            case 3:
        		                e3.add(personF, order, personTF);
        		                break;
        		            case 4:
        		                e4.add(personF, order, personTF);
        		                break;

        		        }

        		        order = 0;
        		    }
        		    else if(-1 == order)//下降按钮
        		    {
        		        int personF = new Integer(personFloor.getText());
        		        int personTF = new Integer(personToFloor.getText());

        		        //逻辑判断 电梯最优方案
        		        int e1Distance = e1.countDistance(personF, order);
        		        int e2Distance = e2.countDistance(personF, order);
        		        int e3Distance = e3.countDistance(personF, order);
        		        int e4Distance = e4.countDistance(personF, order);
        		        int result = whoIsRun(e1Distance,e2Distance,e3Distance,e4Distance);
        		        switch(result){
        		            case 1:
        		                e1.add(personF, order, personTF);
        		                break;
        		            case 2:
        		                e2.add(personF, order, personTF);
        		                break;
        		            case 3:
        		                e3.add(personF, order, personTF);
        		                break;
        		            case 4:
        		                e4.add(personF, order, personTF);
        		                break;

        		        }

        		        order = 0;
        		    }
        		    //清理屏幕
        		    screen1.setText(controller1.getInfo());
        		    screen2.setText(controller2.getInfo());
        		    screen3.setText(controller3.getInfo());
        		    screen4.setText(controller4.getInfo());
        		}
         }
     public static void main(String[] args) {
      new elevator();
     }
 }
class Controller implements Runnable {
    Elevator Elevator = null;
    String info = null;
    Controller(Elevator e) {
        this.Elevator = e;
    }

    public String getInfo() {
        return info;
    }

    public void run() {
        while (true) {
            try {
                Elevator.run();
                info = Elevator.show();
            } catch (Exception e1) {
                e1.printStackTrace();
            }
            try {
                Thread.sleep(3000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Elevator {
    private int id;
    private int maxLoadWeight;
    private int loadWeight;
    private int state;
    private int floor;
    private int runState;
    private int[] toFloors;
    private int start, end;
    private String info;

    Elevator(int id, int maxLoadWeight, int state) {
        this.id = id;
        this.maxLoadWeight = maxLoadWeight;
        this.loadWeight = 0;
        this.state = state;
        this.setFloor(1);
        this.setRunState(0);
        toFloors = new int[20];
        this.start = 0;
        this.end = 0;
    }

    public int countDistance(int personFloor, int runDirection) {
        if (state == 1 && (personFloor % 2) == 0)
            return 100;
        if (state == 2 && (personFloor % 2) == 1)
            return 100;
        if (end == start)
            return Math.abs(personFloor - floor);
        else if (end - start == 1) {
            if (toFloors[end - 1] > floor) {
                if (1 == runDirection) {
                    if (personFloor < floor) {
                        return (toFloors[end - 1] - floor) * 2 + (floor - personFloor);
                    } else {
                        return personFloor - floor;
                    }
                } else {
                    if (personFloor > toFloors[end - 1]) {
                        return personFloor - floor;
                    } else if (personFloor < floor) {
                        return (toFloors[end - 1] - floor) * 2 + (floor - personFloor);
                    } else {
                        return (toFloors[end - 1] - floor) + (personFloor - floor);
                    }
                }
            } else {
                if (1 == runDirection) {
                    if (personFloor > floor) {
                        return (floor - toFloors[end - 1]) * 2 + (personFloor - floor);
                    } else if (personFloor < toFloors[end - 1]) {
                        return floor - personFloor;
                    } else {
                        return (floor - toFloors[end - 1]) + (personFloor - toFloors[end - 1]);
                    }
                } else {
                    if (personFloor > floor) {
                        return (floor - toFloors[end - 1]) * 2 + (personFloor - floor);
                    } else if (personFloor < toFloors[end - 1]) {
                        return floor - personFloor;
                    }
                }
            }
        } else {
            if (toFloors[end - 1] > toFloors[end - 2]) {
                if (1 == runDirection) {
                    if (personFloor < toFloors[end - 2]) {
                        return (toFloors[end - 1] - toFloors[end - 2]) * 2 + (toFloors[end - 2] - personFloor);
                    } else {
                        return personFloor - toFloors[end - 2];
                    }
                } else {
                    if (personFloor > toFloors[end - 2]) {
                        return personFloor - toFloors[end - 2];
                    } else if (personFloor < toFloors[end - 2]) {
                        return (toFloors[end - 1] - toFloors[end - 2]) * 2 + (toFloors[end - 2] - personFloor);
                    }
                }
            } else {
                if (1 == runDirection) {
                    if (personFloor > toFloors[end - 2]) {
                        return (toFloors[end - 2] - toFloors[end - 1]) * 2 + (personFloor - toFloors[end - 2]);
                    } else if (personFloor < toFloors[end - 2]) {
                        return toFloors[end - 2] - personFloor;
                    } else {
                        return (toFloors[end - 2] - toFloors[end - 1]) + (personFloor - toFloors[end - 2]);
                    }
                } else {
                    if (personFloor > toFloors[end - 2]) {
                        return (toFloors[end - 2] - toFloors[end - 1]) * 2 + (personFloor - toFloors[end - 2]);
                    } else if (personFloor < toFloors[end - 2]) {
                        return toFloors[end - 2] - personFloor;
                    }
                }
            }
        }
        return -100;//防止出错判断   
    }
    public void add(int personFloor, int runDirection, int toFloor) {
        if (end - start > 0) {
            if ((toFloors[end-1] - toFloors[end - 2])*runDirection > 0) {
                if (1 == runDirection) {
                    if (personFloor > toFloors[end - 1]) {
                        toFloors[(end++) % 20] = personFloor;
                        toFloors[(end++) % 20] = toFloor;
                    } else {
                        toFloors[end] = toFloors[(end++)%20 -1];
                        toFloors[end - 2] = personFloor;
                        if (toFloor > toFloors[end - 1])
                            toFloors[(end++) % 20] = toFloor;
                        else{    
                            toFloors[end] = toFloors[end - 1];
                            toFloors[end - 1] = toFloor;
                            end = (end++) % 20;
                        }
                    }
                } else {
                    if (personFloor < toFloors[end - 1]) {
                        toFloors[(end++) % 20] = personFloor;
                        toFloors[(end++) % 20] = toFloor;
                    }
                    else {//人所在楼层 高于 电梯去的最低楼层
                        toFloors[end] = toFloors[end - 1];
                        toFloors[end - 1] = personFloor;
                        end = (end++)%20;
                        if (toFloor < toFloors[end - 1])//人要去楼层低于电梯所在楼层
                            toFloors[(end++) % 20] = toFloor;
                        else {    //人要去楼层高于电梯所在楼层
                            toFloors[end] = toFloors[end - 1];
                            toFloors[end - 1] = toFloor;
                            end = (end++) % 20;
                        }
                    }
                }
            }
            else { // 反方向  
                toFloors[(end++) % 20] = personFloor;  
                toFloors[(end++) % 20] = toFloor;  
            }  
        }     
        else // 电梯目标楼层数量为1或者0  
          {  
                toFloors[(end++) % 20] = personFloor;  
                toFloors[(end++) % 20] = toFloor;  
          }  
    }         
            public void run() throws Exception // 电梯运行  
            {  
                if (start != end) // 需要运行  
                {  
                    if (floor < toFloors[start]) // 向上  
                    {  
                        runState = 1;  
                        floor++;  
                    }  
                    else if (floor > toFloors[start]) // 向下  
                    {  
                        runState = -1;  
                        floor--;  
                    }  
                    else // floor = toFloors[start] 到目的地  
                    {  
                        System.out.println("电梯" + id + " 已到达到达目的地:" + floor);  
                        runState = 0;  
                        start = (start + 1) % 20;  
                    }  
                }  
            }
            public String show(){  
                info = id + "'s Elevator \non " + floor + "'s floor\nis ";  
                if (1 == runState)  
                    return info + " ↑";  
                if (-1 == runState)  
                    return info + " ↓";  
                return info + " -- ";  
            }  
              
            public int getRunState() {  
                return runState;  
            }  
              
            public void setRunState(int runState) {  
                this.runState = runState;  
            }  
              
            public int getFloor() {  
                return floor;  
            }  
              
            public void setFloor(int floor) {  
                this.floor = floor;  
            }
        }






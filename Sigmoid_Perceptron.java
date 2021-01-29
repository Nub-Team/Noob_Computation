//Sigmoid Perceptron

package perceptron;

import java.util.Random;

public class Perceptron {
    private Random ran = new Random();   
    private double eta=0.7;
    private double w1=0;
    private double w2=0;
    private double b1=0;

    double boolTdouble(boolean in){
        if(in){
            return 1.0;
        }else{
            return 0.0;
        }
    }

    private double neural(double x1,double x2,double d){
        double n=w1*x1+w2*x2+b1;	
        double o =1/(1+Math.pow(Math.E,(-1*n)));
  
        w1+=eta*(d-o)*o*(1-o)*x1;
        w2+=eta*(d-o)*o*(1-o)*x2;
        b1+=eta*(d-o)*o*(1-o)* 1;	
        return (d-o);
    }
    
    public void neuralAND(){
       boolean x=ran.nextBoolean();
       boolean y=ran.nextBoolean();
       boolean z=x&y;
       System.out.println(neural(boolTdouble(x),boolTdouble(y),boolTdouble(z)));
    }

    public void neuralOR(){
       boolean x=ran.nextBoolean();
       boolean y=ran.nextBoolean();
       boolean z=x|y;
       System.out.println(neural(boolTdouble(x),boolTdouble(y),boolTdouble(z)));
    }

    public void neuralXOR(){
       boolean x=ran.nextBoolean();
       boolean y=ran.nextBoolean();
       boolean z=x^y;
       System.out.println(neural(boolTdouble(x),boolTdouble(y),boolTdouble(z)));
    }

    public void init(){
        w1=ran.nextDouble();
        w2=ran.nextDouble();
        b1=ran.nextDouble();
    }
    
    public static void main(String[] args) {
        Perceptron neural=new Perceptron();
        neural.init();
        for(int i=0;i<5000;i++){
            neural.neuralAND();
	    }
    }
    //Coded by -> MatondangR
}

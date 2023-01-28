import java.util.Scanner;	//���ǹ�

public class Practice01 {

	public static void main(String[] args) {
		
		//ex1();
		//ex2();
		//ex3();
		//ex4();
		//ex5();
		//ex6();
		//ex7();
		//ex8();
		ex9();
		//ex10();
		
	} //main
	
	public static void ex10() {
		
		int n;

        Scanner scanner = new Scanner(System.in);

        System.out.print("���� �Է� : ");
        n = scanner.nextInt();

        if (n < 1 || n > 99)
            return;

        for (int i = 1; i <= n; ++i) {
            System.out.print(i);

            // 3, 6, 9 �� �� ���ִ��� ���ϴ�
            int count = 0;
            // 10 �� �ڸ��� 3, 6, 9 �� ���� ���
            if (i / 10 == 3 || i / 10 == 6 || i / 10 == 9)
                ++count;
            // 1 �� �ڸ��� 3, 6, 9 �� ���� ���
            if (i % 10 == 3 || i % 10 == 6 || i % 10 == 9)
                ++count;

            // ��� ���
            if (count == 2)
                System.out.println(" --- ¦¦");
            else if (count == 1)
                System.out.println(" --- ¦");
            else
                System.out.println();
        }	    
}//ex10
     
	
	
	//3-4 10���� ���� @@@@@@@@@@@@@@@@@@@@
		public static void ex9() {
			System.out.println("���ڸ� �Է��ϼ���.");
			Scanner sc = new Scanner(System.in);
			int n = sc.nextInt();
			int reverse = 0;
			
			while (n != 0) {
				int digit = n % 10;
				reverse = reverse * 10 + digit;
				n /= 10;		
			if(n<=0) {
				break;
			}
			}
			System.out.println(reverse);
			
				}	
	
	
	
	//3-3 0123456789 3���� ��� ��� @@@@@@@@@@@@@@@@@
	public static void ex8() {
		int i,j;
		
		for ( i=0;i<10;i++) {
			System.out.println("");
			for (j=0; j<10;j++) {
				if(i<= j)
					System.out.print(j);
				else
					System.out.print(" ");
				
			}	
		}
		
	}
	
	
	
	
	public static void ex7() {
		int i,j;
		
		for ( i=9;i>=0;i--) {
			System.out.println("");
			for (j=0; j<10;j++) {
				if(i>= j)
					System.out.print(j);
			}	
		}
		
	}
	
	
	
	
	public static void ex6() {
		int i,j;
		
		for ( i=0;i<=4;i++) {
			System.out.println("");
			for (j=0; j<=9;j++) {
			System.out.print(j);
			}	
		}
		
	}
	
	//3-2 ���������� 5X4������ ���� ��� @@@@@@@@@@@@@@@@@@
	public static void ex5() {
		double x;
		int i,j;
		
		for ( i=1;i<=5;i++) {
			System.out.println("");
			for (j=1; j<=4;j++) {
			 x= Math.random();
			System.out.print((int)(x*9+1) + " ");
			}	
		}
		
	}
	
	
	
	// 3-1 �����Է� 3�� ����� �հ����   @@@@@@@@@@@@@@@@@@@@
		public static void ex4() {
			int sum = 0;
			Scanner scanner = new Scanner(System.in);
			System.out.println("3�� ����� �հ踦 ���. 0 �Ǵ� ���� �Է½� �ߴ�");
			
			int n = scanner.nextInt();
			
			while (n > 0 ) { 
				if ( n % 3 == 0) {
					sum += n;
					}	
			n = scanner.nextInt();
				if (n <= 0 ) {
					break;
					}
		}
			System.out.print("�հ�� " + (double)sum +" �Դϴ�.");
		
			Scanner close;
	}
	
	//2-5 �����Է� ��Ģ����� @@@@@@@@@@@@@@@@@@@@@@@@@@
	public static void ex3(){
	Scanner scanner = new Scanner(System.in);
	
	System.out.println("�����Է�(�����ھյ� ����):");
	
	double op1,op2;
	char opr;
	
	op1 = scanner.nextDouble();
	opr = scanner.next().charAt(0);
	op2 = scanner.nextDouble();
	
	double sum = op1 + op2;
	double min = op1 - op2;
	double mul = op1 * op2;
	double dis = op1 / op2;
	double ex = op1 % op2;
	
	//str = String.valueIf(c); -> ���ڸ� ���ڿ��� ��ȯ
	
	switch(opr) {
	
	case '+':
		System.out.println(op1 + " + " + op2 + " = " + sum  );
		break;
	case '-':
		System.out.println(op1 + " - " + op2 + " = " + min  );
		break;
	case '*':
		System.out.println(op1 + " * " + op2 + " = " + mul  );
		break;
	case '/':
		System.out.println(op1 + " / " + op2 + " = " + dis  );
		if (op2 == 0)
			System.out.println("0���� ������ �����ϴ�.");
		break;
	case '%':
		System.out.println(op1 + " % " + op2 + " = " + ex  );
		break;
	
	default :
		
	
		System.out.printf("�����߻�");
	
	}
	
		scanner.close();		
}//ex3
	
	
	
	//�������ϱ� & Excellent/Sorry/Umm ���@@@@@@@@@@@@@@@
	public static void ex2() {Scanner scanner = new Scanner(System.in);
	
	System.out.println("������ �Է��ϼ���(0~100)");
	int score = scanner.nextInt();
	
	String grade;
	
	//switch() // ����, ����, ���ڿ��� ����    /  �����, ���� ,���� ��� �Ұ���
	if (score > 100 || score <0)
		System.out.println("�Է¿���");
		if(score<=100 && score >95)
			grade = "A+";
		else if (score<=95 && score >90)
			grade = "A0";
		else if (score<=90 && score >85)
			grade = "B+";
		else if (score<=85 && score >80)
			grade = "B0";
		else if (score<=80 && score >=0)
			grade = "F";
		else
			grade = "�Է¿���";
	
	if (grade != "�Է¿���")
	System.out.println(grade);
	
	char g = grade.charAt(0);	//�Է¹��� grade �� ù ����(0�� ù ��°��)�� g �� ����
	
	switch(g) {
		case 'A':
		System.out.println("Excellent");
			break;
		case 'B':
		System.out.println("Sorry");
			break;
		case 'F':
		System.out.println("Umm");
		break;
		}
	} //ex2
	
	//2-3 Ŀ���ֹ� & ����  @@@@@@@@@@@@@@@@@@@@@@@@
	public static void ex1() {
		Scanner scanner01 = new Scanner(System.in);
		Scanner scanner02 = new Scanner(System.in);
		
		System.out.println("����������? �Ƹ޸�ī��?");
		String order = scanner01.next(); //�ֹ��б�
		
		System.out.println("�� ��?");
		int many = scanner02.nextInt();
		
		if (order.equals("����������"))
			if (many >=7)
				System.out.println(1800*many);
			else
				System.out.println(2000*many);
	else if (order.equals("�Ƹ޸�ī��"))
			if (many>=5)
				System.out.println(2250*many);
			else
				System.out.println(2500*many);
	else
		System.out.println("�ٽ��ֹ��ϼ���");
			
		scanner01.close();
		scanner02.close();
		}//ex1
	
} //class

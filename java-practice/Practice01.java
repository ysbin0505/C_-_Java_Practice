import java.util.Scanner;	//조건문

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

        System.out.print("정수 입력 : ");
        n = scanner.nextInt();

        if (n < 1 || n > 99)
            return;

        for (int i = 1; i <= n; ++i) {
            System.out.print(i);

            // 3, 6, 9 가 몇 개있는지 셉니다
            int count = 0;
            // 10 의 자리에 3, 6, 9 가 있을 경우
            if (i / 10 == 3 || i / 10 == 6 || i / 10 == 9)
                ++count;
            // 1 의 자리에 3, 6, 9 가 있을 경우
            if (i % 10 == 3 || i % 10 == 6 || i % 10 == 9)
                ++count;

            // 결과 출력
            if (count == 2)
                System.out.println(" --- 짝짝");
            else if (count == 1)
                System.out.println(" --- 짝");
            else
                System.out.println();
        }	    
}//ex10
     
	
	
	//3-4 10진수 분해 @@@@@@@@@@@@@@@@@@@@
		public static void ex9() {
			System.out.println("숫자를 입력하세요.");
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
	
	
	
	//3-3 0123456789 3가지 모양 출력 @@@@@@@@@@@@@@@@@
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
	
	//3-2 랜덤값으로 5X4형태의 정수 출력 @@@@@@@@@@@@@@@@@@
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
	
	
	
	// 3-1 정수입력 3의 배수만 합계출력   @@@@@@@@@@@@@@@@@@@@
		public static void ex4() {
			int sum = 0;
			Scanner scanner = new Scanner(System.in);
			System.out.println("3의 배수만 합계를 출력. 0 또는 음수 입력시 중단");
			
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
			System.out.print("합계는 " + (double)sum +" 입니다.");
		
			Scanner close;
	}
	
	//2-5 수식입력 사칙연산기 @@@@@@@@@@@@@@@@@@@@@@@@@@
	public static void ex3(){
	Scanner scanner = new Scanner(System.in);
	
	System.out.println("수식입력(연산자앞뒤 띄어쓰기):");
	
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
	
	//str = String.valueIf(c); -> 문자를 문자열로 변환
	
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
			System.out.println("0으로 나눌수 없습니다.");
		break;
	case '%':
		System.out.println(op1 + " % " + op2 + " = " + ex  );
		break;
	
	default :
		
	
		System.out.printf("오류발생");
	
	}
	
		scanner.close();		
}//ex3
	
	
	
	//학점구하기 & Excellent/Sorry/Umm 출력@@@@@@@@@@@@@@@
	public static void ex2() {Scanner scanner = new Scanner(System.in);
	
	System.out.println("점수를 입력하세요(0~100)");
	int score = scanner.nextInt();
	
	String grade;
	
	//switch() // 정수, 문자, 문자열만 가능    /  연산식, 조건 ,변수 사용 불가능
	if (score > 100 || score <0)
		System.out.println("입력오류");
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
			grade = "입력오류";
	
	if (grade != "입력오류")
	System.out.println(grade);
	
	char g = grade.charAt(0);	//입력받은 grade 의 첫 글자(0이 첫 번째임)를 g 로 선언
	
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
	
	//2-3 커피주문 & 할인  @@@@@@@@@@@@@@@@@@@@@@@@
	public static void ex1() {
		Scanner scanner01 = new Scanner(System.in);
		Scanner scanner02 = new Scanner(System.in);
		
		System.out.println("에스프레소? 아메리카노?");
		String order = scanner01.next(); //주문읽기
		
		System.out.println("몇 잔?");
		int many = scanner02.nextInt();
		
		if (order.equals("에스프레소"))
			if (many >=7)
				System.out.println(1800*many);
			else
				System.out.println(2000*many);
	else if (order.equals("아메리카노"))
			if (many>=5)
				System.out.println(2250*many);
			else
				System.out.println(2500*many);
	else
		System.out.println("다시주문하세용");
			
		scanner01.close();
		scanner02.close();
		}//ex1
	
} //class

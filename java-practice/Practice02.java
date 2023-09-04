import java.util.Scanner;		//배열 및 매소드
public class Practice02 {

	public static void main(String[] args) {
	
		//foreachEx();
		//array2DTest();
		//methodTest();
		array2dMethodTest();
		//ExceptionTest();
		
		
		}//main
	
	public static void ExceptionTest() {
		
		Scanner in = new Scanner(System.in);
		
		int i = 0 ;
		double d = 0;
		boolean isInt=false, isDouble=false;
		
		
		System.out.println("정수, 실수 또는 문자열 입력 : ");
		
		String str = in.next();
		
		try {
		
		i = Integer.parseInt(str);	//str값을 인트로 변환
		isInt=true;
		System.out.println("int = " + i);
		
		}
		catch(NumberFormatException e)
		{
			try {
			d= Double.parseDouble(str);
			isDouble = true;
			
			}
			catch(NumberFormatException e1)
			{
				
			}
		}
		
		finally {
			if(isInt) {
				System.out.println("int 변환가능, Double 변환가능");
			}
			else if (isDouble) {
				System.out.println("double = " + d);
				System.out.println("Double 변환가능");
			}
			else {
				System.out.println("only String만 가능");
			}
		
		}
		
		
	}//ExceptionTest
	
	
	public static int[][] randomArr(){		//난수생성 문장@@@
		
		int arr[][] = new int[3][4];
		//int arr[][];
		//arr = new int [3][4];	new로 생성된 것은 지역변수가 아니라 사라지지않음.
		
		for(int i=0; i<arr.length; i++) {
			for(int j=0 ; j<arr[i].length; j++) //arr[0].length -> 0행에 붙어있는 길이
				arr[i][j]=(int)(Math.random() * 10);
		}//난수 생산 프로그램
		return arr;
	}
	
	public static void printArr(int arr[][]){	//출력하는 문장@@@	굳이 arr말고 다른거 써도 됌 하지만 밑도 바꿔야하기때문에 귀찮
		for(int i=0; i<arr.length; i++) {
			for(int j=0 ; j<arr[i].length; j++) 
				System.out.print(arr[i][j] + "\t");
			System.out.println();
		}//출력 프로그램
		return;
	}
	
	public static int makeSum(int arr[][]){	//합계 및 총합계 구하는 문장@@@
		
		int sum = 0;	
		int sumAll = 0;
		
		for(int i=0; i<arr.length; i++) {//sum=0; 여기다가 해도 됌
			for(int j=0 ; j<arr[i].length; j++) 
				sum += arr[i][j];	//한 행이 끝났다는 것은 j가 한바퀴 돌았다는 것
			System.out.println(i+ "행 합계 = " + sum);
			sumAll += sum;	
			sum = 0;	//한 행 지날 때 마다 초기화
		}//합계 및 총 합계 출력 프로그램
		return sumAll;
	}
	
	public static void array2dMethodTest() {	//위에꺼 다 빼주니 깔끔
		
		randomArr();	//위에꺼 불러옴
		
		int arr[][] = randomArr();	//위에꺼를 대입
		printArr(arr);
		int sumAll = makeSum(arr);
		
		System.out.println("====총 합계 = " + sumAll);
		
		
	}//array2DTest
	
	
	
	
	public static String makeLevel(int m) {
		String level;
		switch(m) {
		case 7 : case 8:
			level = "1++";
			break;
		case 6:
			level = "1+";
			break;
		case 5: case 4:
			level = "1";
			break;
		case 3: case 2:
			level = "2";
			break;
		case 1:
			level = "3";
			break;
		default :
			level = "???";
			
		}
		
		return level;
	}
	
	public static void methodTest() {
		Scanner in = new Scanner(System.in);
		while(true) {	//반복하려면 입력부터 출력까지
			System.out.println("근내지방도 입력(marbling 정수 ) : ");
			int marbling = in.nextInt();	//내가 입력한 정수를 마블링에 저장
			String level;					//레벨 문자열 선언
			level = makeLevel(marbling);	//위에 적은 메이크레벨에 내가 저장한 마블링 수 대입
			System.out.println(level);		//위에 해당하는 레벨 출력
			if(level.equals("???"))			//종료 조건
				break;
		}
	
	}//methodTest
	
	
	//String.valueOf("A00" + i); -> 배열 생산 후 값 넣기
	
	public static void array2DTest() {
		int arr[][] = new int[3][4];
		//int arr[][];
		//arr = new int [3][4];	new로 생성된 것은 지역변수가 아니라 사라지지않음.
		
		for(int i=0; i<arr.length; i++) {
			for(int j=0 ; j<arr[i].length; j++) //arr[0].length -> 0행에 붙어있는 길이
				arr[i][j]=(int)(Math.random() * 10);
		}//난수 생산 프로그램
		
		for(int i=0; i<arr.length; i++) {
			for(int j=0 ; j<arr[i].length; j++) 
				System.out.print(arr[i][j] + "\t");
			System.out.println();
		}//출력 프로그램
		
		int sum = 0;	
		int sumAll = 0;
		
		for(int i=0; i<arr.length; i++) {//sum=0; 여기다가 해도 됌
			for(int j=0 ; j<arr[i].length; j++) 
				sum += arr[i][j];	//한 행이 끝났다는 것은 j가 한바퀴 돌았다는 것
			System.out.println(i+ "행 합계 = " + sum);
			sumAll += sum;	
			sum = 0;	//한 행 지날 때 마다 초기화
		}//합계 및 총 합계 출력 프로그램
		System.out.println("====총 합계 = " + sumAll);
		
		
	}//array2DTest
	
	
	
	public static void foreachEx() {
		Scanner scanner = new Scanner(System.in);
		System.out.println("5개의 정수를 입력하시오.(3의 배수만 출력)");
		
		int arr[] = new int[5];
		
		
		for(int i=0 ; i<arr.length ; i++ )
			arr[i] = scanner.nextInt();
		
		for(int i=0 ; i<arr.length ; i++ )
			System.out.print(arr[i] + "\t");	//배열 전체 출력
		System.out.println();
		
		int cnt = 0;
		for( int n : arr)	//n는 배열 전체
		{
			if(n % 3 != 0)	//3의 배수가 아닐때
				continue;	//넘어가고
			System.out.print(n + " ");	//3의 배수일때 출력
			cnt++;
		}	
		System.out.println("(" + cnt + "개)");
		
		int i = 0;
		for(int n : arr)	//n은 배열 전체	
		{
			arr[i++] *= 10; //n *= 10; 배열이 바뀌지 않음 arr[i++]처럼 배열에 곱해줘야함.
		}
		for (int n : arr)	//*10이된 배열들 출력
			System.out.print(n + " ");
		
}//foreachEx
	
	}//class

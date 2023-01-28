import java.util.Scanner;	//예외처리
public class Practice03 {

	public static void main(String[] args) {
		
		ExceptionTest();
		
	
	}//main
	
public static void ExceptionTest() {
		
		Scanner in = new Scanner(System.in);
		
		int i = 0 ;
		double d = 0;
		
		while(true) {
		
		boolean isInt=false, isDouble=false;
		
		
		System.out.println("정수, 실수 또는 문자열 입력 : ");
		
		String str = in.next();
		if(str.equals("stop"))
		break;
		
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
				System.out.println("Double 형태");
			}
			else {
				System.out.println("only String만 가능");
			}
		
		}
		}	
		System.out.println("종료합니다.");
	}//ExceptionTest
	
	
}//class
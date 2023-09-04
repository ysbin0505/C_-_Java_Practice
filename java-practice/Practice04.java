import java.util.Scanner;

public class Practice04 {

	public static void main(String[] args) {
	//돈 액수를 입력받아 오만원권 만원권 오천원권 천원권 몇 개로 변환하고 얼마나 남는지 출력하는 프로그램
		
		Scanner scanner = new Scanner(System.in);
		
		int a = scanner.nextInt();
		
		int b = a/50000;
		int c = a%50000/5000;
		int d = a%50000%5000/1000;
		int e = a%50000%5000%1000;
		
		System.out.print(a + "는 " + "오만원권 " + b + "장, 오천원권 " + c + "장, 천원권 " + d + "장, 나머지는 " + e + "원" );
		
	}
}
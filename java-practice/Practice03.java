import java.util.Scanner;	//����ó��
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
		
		
		System.out.println("����, �Ǽ� �Ǵ� ���ڿ� �Է� : ");
		
		String str = in.next();
		if(str.equals("stop"))
		break;
		
		try {
		
		i = Integer.parseInt(str);	//str���� ��Ʈ�� ��ȯ
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
				System.out.println("int ��ȯ����, Double ��ȯ����");
			}
			else if (isDouble) {
				System.out.println("double = " + d);
				System.out.println("Double ����");
			}
			else {
				System.out.println("only String�� ����");
			}
		
		}
		}	
		System.out.println("�����մϴ�.");
	}//ExceptionTest
	
	
}//class
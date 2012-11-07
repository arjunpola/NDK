
public class Array
{
	static { System.loadLibrary("native-arr");}

	public native void printIntArr(int[] arr);
	public native int getIntArrSum(int[] arr);
	public native void printCharArr(char[] arr);
	public native int[] makeIntArr(int len);
	public native char[] makeCharArr(int len);

	public static void main(String[] args)
	{
		Array a = new Array();

		int[] intArr = { 1,2,3,4,5,6,7,8,9 };
		a.printIntArr(intArr);
		
		System.out.println("Java print arr sum : " + a.getIntArrSum(intArr));

		char[] charArr = { 'a','b','c','d','e','f','g'};
		a.printCharArr(charArr);

		System.out.println("------------------------------------------------");

		int [] intArr2 = a.makeIntArr(5);
		System.out.print(" [Java] int Arr form c = ");
		for(int i : intArr2)
			System.out.print("["+i+"]");
		System.out.println(" ");

		char [] intChar2 = a.makeCharArr(5);
		System.out.print(" [Java] Char Arr form c = ");
		for(char c : intChar2)
			System.out.print("["+c+"]");
		System.out.println(" ");
	}
}

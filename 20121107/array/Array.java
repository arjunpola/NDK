
public class Array
{
	static { System.loadLibrary("native-arr");}

	public native void printIntArr(int[] arr);

	public native int getIntArrSum(int[] arr);

	public static void main(String[] args)
	{
		Array a = new Array();

		int[] intArr = { 1,2,3,4,5,6,7,8,9 };
		a.printIntArr(intArr);
		
		System.out.println("Java print arr sum : " + a.getIntArrSum(intArr));
	}
}


public class Calc
{
	static { System.loadLibrary("native-calc"); }

	public native int add(int a,int b);
	public native int sub(int a,int b);

	public static native String getHelloWorld();

	public static void main(String [] arg)
	{
		Calc c = new Calc();

		System.out.println(" 3 + 4 = " + c.add(4,3));
		System.out.println(" 3 - 4 = " + c.sub(4,3));

		System.out.println("Java print : " + getHelloWorld());
	}
}

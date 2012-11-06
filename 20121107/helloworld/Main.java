package test;

public class Main
{
	static { System.loadLibrary("native-hello");}

	public static native void printHelloWorld();

	public static void main(String [] arg)
	{
		printHelloWorld();
	}
}

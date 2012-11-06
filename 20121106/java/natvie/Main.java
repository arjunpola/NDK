package test;


public class Main
{
	static { 
		System.loadLibrary("native-hello");
		System.loadLibrary("native-goodbye");	
	}

	public static native void printHelloWorld();
	public static native void printGoodbye();

	public static void main(String [] args)
	{
		printHelloWorld();
		printGoodbye();

	}

}

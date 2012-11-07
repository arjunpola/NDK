
public class Main
{
	// libmath.so
	static { System.loadLibrary( "math" ); }

	public static native Math createMathObject();

	public static void main(String[] args)
	{
		Math m = createMathObject();

		System.out.println( "[Java] 4 + 3 = " + m.add(4,3));
		System.out.println( "[Java] 4 - 3 = " + m.sub(4,3));
	}
}

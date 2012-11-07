

public class Main 
{
	static { System.loadLibrary( "circle" ); }

	public native static float getCircleArea(int r);

	public static void main(String[] arg)
	{
		System.out.println("[JAVA] area of circle(3) = " + getCircleArea(3));
		System.out.println("[JAVA] area of circle(4) = " + getCircleArea(4));
	}
}

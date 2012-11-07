
public class Type
{
	static { System.loadLibrary("native-type");}

	public native void printInt(int i);
	public native void printChar(char c);
	public native void printShort(short s);
	public native void printLong(long l);
	public native void printFloat(float f);
	public native void printDouble(double d);
	public native void printBoolean(boolean b);

	public static void main(String [] arg)
	{
		Type t = new Type();
		t.printInt(444);

		char c = 'A';
		t.printChar(c);

		short s = (short)666;
		t.printShort(s);
		
		long l = (long)66565;
		t.printLong(l);

		float f = (float)54.3;
		t.printFloat(f);

		double d = (double)0.2134;
		t.printDouble(d);

		boolean b = true;
		t.printBoolean(b);
	}
}


public class Type
{
	static { System.loadLibrary("native-type");}

	public native void printInt(int i);

	public static void main(String [] arg)
	{
		Type t = new Type();
		t.printInt(444);
	}
}

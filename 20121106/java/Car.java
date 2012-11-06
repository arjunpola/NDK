
public class Car 
{
	private String name;
	private int door;
	private String color;
	
	public Car()
   	{
		this("i30",4,"Silver");
	}


	public Car(String name,int door,String color)
	{
		this.name = name;
		this.door = door;
		this.color = color;
	}

	public void setName(String name){ this.name = name; }
	public void setDoor(int door){ this.door = door; }
	public void setColor(String color){ this.color = color; }

	public void show()
	{
		System.out.println("name = " + name);
		System.out.println("door = " + door);
		System.out.println("color = " + color);
	}

}

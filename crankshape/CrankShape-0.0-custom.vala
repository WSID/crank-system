namespace Crank {

  struct Box2 {
    public Box2 (  Crank.VecFloat2 start,
                   Crank.VecFloat2 end );
    public Box2.uvec ( float start_x,
                       float start_y,
                       float end_x,
                       float end_y);

    public Box2.range (Crank.RanFloat x,
                       Crank.RanFloat y);

    public Box2.unit ();
    
    public Crank.RanFloat	x {get; }
    public Crank.RanFloat	y {get; }
    
    public Crank.VecFloat2	dimen {get; }
    public float			diaglen {get; }
  }


  struct Euler {
    public Euler ();
    public Euler.angle (    float           angle1,
                            float           angle2,
                            float           angle3,
                            Crank.EulerType etype);
    public Euler.from_quaternion (  Crank.QuatFloat quat,
                                    Crank.EulerType etype);
    public Euler.from_matrix3 (     Crank.MatFloat3 mat,
                                    Crank.EulerType etype);
    public Euler.from_matrix4 (     Crank.MatFloat4 mat,
                                    Crank.EulerType etype);
  }
  
  struct Trans2 {
    public Trans2 ();
    public Trans2.from_matrix (Crank.MatFloat3 mat);
  }

  [Compact]
  public class PolyStruct3 {
    public uint nvertices { get; set; }
    public uint nedges { get; }
    public uint nfaces { get; }
  }
}

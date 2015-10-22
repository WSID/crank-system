namespace Crank {
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
}

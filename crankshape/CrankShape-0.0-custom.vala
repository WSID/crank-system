namespace Crank {
  struct Euler {
    public Euler ();
    public Euler.angle (    float yaw,
                            float pitch,
                            float roll);
    public Euler.from_quaternion (  Crank.QuatFloat quat);
    public Euler.from_matrix3 (     Crank.MatFloat3 mat);
    public Euler.from_matrix4 (     Crank.MatFloat4 mat);
  }
  
  struct Trans2 {
    public Trans2 ();
    public Trans2.from_matrix (Crank.MatFloat3 mat);
  }
}

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

  public delegate unowned Crank.VecFloat3 OctreePosFunc <G> (G data);
  public delegate float                   OctreeRadiusFunc <G> (G data);

  [Compact]
  [CCode (ref_function="crank_octree_set_ref", unref_function="crank_octree_set_unref", simple_generics=true)]
  public class OctreeSet <G> {
    [Compact]
    [CCode (simple_generics=true)]
    public class Node <G> {
      private Node ();
      public Crank.Box3 boundary { owned get; }
      public Crank.VecFloat3 middle { owned get; }

      public bool has_children ();
      public Crank.OctreeSet.Node <G> get_child (uint index);
      public Crank.OctreeSet.Node <G> get_child_pos (uint index, Crank.VecFloat3 pos);
    }

    public OctreeSet (Crank.Box3 boundary,
                      owned Crank.OctreePosFunc <G> pos_func,
                      owned Crank.OctreeRadiusFunc <G> rad_func);

    public OctreeSet @ref ();
    [DestroysInstance]
    public void @unref ();


    public uint       size { get; }
    public Crank.Box3 boundary { owned get; }

    public void add (G data);
    public bool remove (G data);
    public void remove_all ();
    public bool contains (G data);


    public void @foreach (GLib.Func <G> func);
    public void cull_foreach (Crank.Plane3[] culls, GLib.Func <G> func);

    public GLib.List <unowned G>?                get_data_list ();
    public unowned GLib.GenericArray <unowned G> add_data_array (GLib.GenericArray <unowned G> array);

    public GLib.List <unowned G>?                get_culled_list (Crank.Plane3[] culls);
    public unowned GLib.GenericArray <unowned G> add_culled_array (GLib.GenericArray <unowned G> array, Crank.Plane3[] culls);


    public Crank.OctreeSet.Node<G> root { get; }

    public Crank.OctreeSet.Node<G>? get_node (G data);
  }
}

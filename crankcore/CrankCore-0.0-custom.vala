namespace Crank {
  public class Session: GLib.Object {
    public bool running {
      [CCode (cname="crank_session_is_running")]get;
      set;
    }
  }

  public class Place3 {
    public Crank.Session3 session {get;}
    public unowned GLib.Object object {get; set;}
    public Crank.Box3 boundary {get; set;}
    public unowned GLib.GenericArray<Crank.Entity3> entities {get;}
  }

  public class Entity3 {
    public Crank.Session3 session {get;}
    public unowned GLib.Object object {get; set;}
    public unowned Crank.Place3 place {get;}
    public Crank.Trans3 position {get; set;}
  }

  public class Session3Module: GLib.Object {
    public bool initialized {
      [CCode (cname="crank_session3_module_is_initialized")]get;
    }
  }
}

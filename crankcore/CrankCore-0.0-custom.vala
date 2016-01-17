namespace Crank {
  public class Session: GLib.Object {
    public bool running {
      [CCode (cname="crank_session_is_running")]get;
      set;
    }
  }
}

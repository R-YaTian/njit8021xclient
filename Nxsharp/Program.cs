using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Configuration;
using System.IO;
using System.Net;
using System.Net.NetworkInformation;
using System.Runtime.InteropServices;
using System.Management;
using System.Resources;


namespace gui
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            
            
            //MessageBox.Show(RefComm.read_log());
            NetworkInterfaceAvaliable.List();            
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            //自动释放DLL
            string path = Application.StartupPath + "/";
            string dllFileName = "xclient.dll";
            if (!File.Exists(path + dllFileName))
            {
                FileStream fs = new FileStream(path + dllFileName, FileMode.CreateNew, FileAccess.Write);
                BinaryWriter bw = new BinaryWriter(fs);
                bw.Write(gui.Properties.Resources.xclient);
                File.SetAttributes(path + dllFileName, FileAttributes.Hidden);
                bw.Close();
                fs.Close();

            }
            string cfgFileName = "NXSharp.exe.Config";
            if (!File.Exists(path + cfgFileName))
            {
                Cfg.CreateFile();
                //不能使用隐藏的配置文件
                MessageBox.Show("首次生成配置文件，请再次打开！");
                return;
            }
            Cfg.Load();
            Application.Run(new Form1());
            RefComm.stop_auth_thread();
            RefComm.exit_dll();
            return;
        }
        
    }
    public class Cfg
    {
        public static string username;
        public static string password;
        public static string device;
        public static bool store = false;
        public static bool auto = false;
        public static void Load()
        {
            try
            {
                Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
                AppSettingsSection app = config.AppSettings;
                Cfg.username = app.Settings["username"].Value;
                Cfg.password = app.Settings["password"].Value;
                Cfg.device = app.Settings["device"].Value;
                Cfg.store = Convert.ToBoolean(app.Settings["store"].Value);
                Cfg.auto = Convert.ToBoolean(app.Settings["auto"].Value);
                return;
            }
            catch (Exception)
            {
                //避免配置文件丢失
                MessageBox.Show("没有找到配置文件！");
                //Form2 f2 = new Form2();
                //f2.ShowDialog();
                return;
                //CreateFile();
                //Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
                //AppSettingsSection app = config.AppSettings;
                //Cfg.username = app.Settings["username"].Value;
                //Cfg.password = app.Settings["password"].Value;
                //throw;
            }
        }
        public static void Commit()
        {
            Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
            AppSettingsSection app = config.AppSettings;
            app.Settings["username"].Value = username;
            app.Settings["password"].Value = password;
            app.Settings["device"].Value = device;
            app.Settings["store"].Value = store.ToString();
            app.Settings["auto"].Value = auto.ToString();
            config.Save();
            return;
        }
        public static void CreateFile()
        {
            string path = Application.StartupPath + "/";
            string cfgFileName = "NXSharp.exe.Config";
            FileStream fs = new FileStream(path + cfgFileName, FileMode.OpenOrCreate, FileAccess.Write);
            StreamWriter sw = new StreamWriter(fs);
            sw.Write(gui.Properties.Resources.NXSharp_exe);
            sw.Close();
            fs.Close();
            return;
        }
        
    }
    public class NetworkInterfaceAvaliable
    {
        public static Dictionary<string, string> adapters_dict = new Dictionary<string, string>();
        public static void List()
        {
            NetworkInterface[] adapters = NetworkInterface.GetAllNetworkInterfaces();
            foreach (NetworkInterface adapter in adapters)
            {
                //if (adapter.NetworkInterfaceType.ToString() == "Ethernet")
                //{
                NetworkInterfaceAvaliable.adapters_dict.Add(adapter.Description, adapter.Id);
                //}
            }
        }
        public static void RefreshDHCP(string device_id)
        {
            //需要手动添加对 System.Management 的引用
            ManagementClass objMC = new ManagementClass("Win32_NetworkAdapterConfiguration");
            ManagementObjectCollection objMOC = objMC.GetInstances();
            foreach (ManagementObject objMO in objMOC)
            {
                //Need to determine which adapter here with some kind of if() statement
                if (objMO["SettingID"].ToString() == device_id)
                {
                    objMO.InvokeMethod("ReleaseDHCPLease", null, null);
                    objMO.InvokeMethod("RenewDHCPLease", null, null);
                }
            }
        }
    }

    public class RefComm
    {
        [DllImport("xclient.dll", EntryPoint = "start_auth_thread", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void start_auth_thread(string username, string password, string device);
        [DllImport("xclient.dll", EntryPoint = "stop_auth_thread", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void stop_auth_thread();
        [DllImport("xclient.dll", EntryPoint = "exit_dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void exit_dll();//增加退出DLL方法
        [DllImport("xclient.dll", EntryPoint = "read_log", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern IntPtr get_log_buffer();
        public static string read_log()
        {
            return Marshal.PtrToStringAnsi(get_log_buffer());
        }

    }
}

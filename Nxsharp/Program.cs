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
            NetworkInterfaceAvaliable.List();            
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Cfg.Load();
            Application.Run(new Form1());
            RefComm.stop_auth_thread();
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
        public static int mode = 0;
        public static void Load()
        {
            //加载配置文件
            try
            {
                ExeConfigurationFileMap map = new ExeConfigurationFileMap();
                map.ExeConfigFilename = Application.StartupPath + "/NXSharp.exe.Config";
                Configuration config = ConfigurationManager.OpenMappedExeConfiguration(map,ConfigurationUserLevel.None);
                AppSettingsSection app = config.AppSettings;
                Cfg.username = app.Settings["username"].Value;
                Cfg.password = app.Settings["password"].Value;
                Cfg.device = app.Settings["device"].Value;
                Cfg.store = Convert.ToBoolean(app.Settings["store"].Value);
                Cfg.auto = Convert.ToBoolean(app.Settings["auto"].Value);
                Cfg.mode = Convert.ToInt32(app.Settings["mode"].Value);
                return;
            }
            catch (Exception)
            {
                //避免配置文件丢失
                MessageBox.Show("没有找到配置文件！");
                return;
            }
        }
        public static void Commit()
        {
            //提交配置文件修改
            ExeConfigurationFileMap map = new ExeConfigurationFileMap();
            map.ExeConfigFilename = Application.StartupPath + "/NXSharp.exe.Config";
            Configuration config = ConfigurationManager.OpenMappedExeConfiguration(map, ConfigurationUserLevel.None);
            AppSettingsSection app = config.AppSettings;
            app.Settings["username"].Value = username;
            app.Settings["password"].Value = password;
            app.Settings["device"].Value = device;
            app.Settings["store"].Value = store.ToString();
            app.Settings["auto"].Value = auto.ToString();
            app.Settings["mode"].Value = mode.ToString();
            config.Save();
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
        public static extern void start_auth_thread(string username, string password, string device,int mode_config);
        [DllImport("xclient.dll", EntryPoint = "stop_auth_thread", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void stop_auth_thread();
        [DllImport("xclient.dll", EntryPoint = "read_log", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern IntPtr get_log_buffer();
        public static string read_log()
        {
            return Marshal.PtrToStringAnsi(get_log_buffer());
        }

    }
}

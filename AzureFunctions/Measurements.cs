using System;
using System.Collections.Generic;
using System.Text;

namespace AzureFunctions
{
    public class Measurements
    {
        public string DeviceIds { get; set; }
        public string School { get; set; }
        public string Name { get; set; }
        public float Temp { get; set; }
        public float Hum { get; set; }
        public int Ts { get; set; }


    }
}

package cf.cafelutza.gg;

import android.annotation.SuppressLint;
import android.os.AsyncTask;
import android.util.Log;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDP_Client {
    private InetAddress IPAddress = null;
    private String message = "OO" ;
    private AsyncTask<Void, Void, Void> async_cient;
    public String Message;

    DatagramSocket ds = null;
    public UDP_Client() {
        try
        {
            ds = new DatagramSocket(9696);

            Log.d("Port: ", String.valueOf(9696));
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public void Close() {
        if (ds != null)
        {
            Log.d("Close: ", "ds");
            ds.close();
        }
    }


    @SuppressLint("NewApi")
    public void Send(String message)
    {
        new Thread(() -> {

            Log.d("Send: ", message);
        try {
            byte[] ipAddr = new byte[]{ (byte) 192, (byte) 168,(byte)4, (byte) 1};
            InetAddress addr = InetAddress.getByAddress(ipAddr);
            DatagramPacket dp;
            dp = new DatagramPacket(message.getBytes(), message.getBytes().length, addr, 9696);
            ds.setBroadcast(true);
            ds.send(dp);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }).start();


        /*
        async_cient = new AsyncTask<Void, Void, Void>()
        {
            @Override
            protected Void doInBackground(Void... params)
            {
                DatagramSocket ds = null;

                try
                {
                    byte[] ipAddr = new byte[]{ (byte) 192, (byte) 168,(byte)4, (byte) 1};
                    InetAddress addr = InetAddress.getByAddress(ipAddr);
                    ds = new DatagramSocket(9696);
                    DatagramPacket dp;
                    dp = new DatagramPacket(Message.getBytes(), Message.getBytes().length, addr, 9696);
                    ds.setBroadcast(true);
                    ds.send(dp);
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
                finally
                {
                    if (ds != null)
                    {
                        ds.close();
                    }
                }
                return null;
            }

            protected void onPostExecute(Void result)
            {
               super.onPostExecute(result);
            }
        };

        if (Build.VERSION.SDK_INT >= 11) async_cient.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
        else async_cient.execute();*/
    }
}

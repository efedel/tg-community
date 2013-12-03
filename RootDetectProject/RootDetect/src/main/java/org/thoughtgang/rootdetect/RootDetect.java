package org.thoughtgang.rootdetect;

import android.util.Log;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

/**
 * Created by prole on 12/2/13.
 */
public class RootDetect {

    /*  This is a simple scan to see if the device has been rooted.
        The Build tags are checked to see if they contain test-keys,
        the most common location of Superuser.apk is checked,
        and the presence of the "su" binary is checked.
     */

    public static final String LOG_TAG = RootDetect.class.getName();

    static final boolean rootP() {
        boolean answer =
                checkBuildTags("test-keys") ||
                checkSuperuserApk("/system/app/Superuser.apk") ||
                runAsRoot(new String[] {"/system/xbin/which", "su"});
        return(answer);
    }

    static boolean tautology() { return(true); }

    static boolean checkBuildTags(String s) {
        String buildTags = android.os.Build.TAGS;
        Log.v(LOG_TAG, "Build Tags: " + buildTags);
        return buildTags != null && buildTags.contains(s);
    }

    static boolean checkSuperuserApk(String s) {
        try {
            File file = new File(s);
            return(file.exists());
        } catch (Exception e) {
            Log.v(LOG_TAG, e.toString());
            Log.v(LOG_TAG, "SuperUser.apk is not in /system/app.");
            return(false);
        }
    }

    static boolean runAsRoot(String[] cmd) {
        ArrayList<String> result = new ArrayList<String>();
        String line = null;

        Process localProcess = null;
        try {
            localProcess = Runtime.getRuntime().exec(cmd);
        } catch (Exception e) {
            Log.v(LOG_TAG, e.toString());
            return(false);
        }

        BufferedWriter out =
                new BufferedWriter(new OutputStreamWriter(localProcess.getOutputStream()));

        BufferedReader in =
                new BufferedReader(new InputStreamReader(localProcess.getInputStream()));

        try {
            while ((line = in.readLine()) != null) {
                Log.v(LOG_TAG, "# " + line);
                result.add(line);
            }

        } catch (Exception e) {
            Log.e(LOG_TAG, e.toString());
            e.printStackTrace();
        }

        Log.v(LOG_TAG, "# " + result);
        return(result != null);

    }


}

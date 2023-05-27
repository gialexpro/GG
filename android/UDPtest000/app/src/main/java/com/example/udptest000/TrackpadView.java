package com.example.udptest000;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.PointF;
import android.view.MotionEvent;
import android.view.View;

public class TrackpadView extends View {

    private final Paint mPaint;
    private Bitmap mBitmap;
    private final Path mPath;
    private final Paint mBitmapPaint;
    final int CLICK = 3;
    Canvas canvas;
    PointF start = new PointF();
    long downStart = 0;
    boolean touching = false;

    // coordinate rounding errors
    private float reX = 0;
    private float reY = 0;


    public TrackpadView(Context c) {
        super(c);

        mPaint = new Paint();
        mPaint.setAntiAlias(true);
        mPaint.setDither(true);

        mPaint.setStyle(Paint.Style.STROKE);
        mPaint.setStrokeJoin(Paint.Join.ROUND);
        mPaint.setStrokeCap(Paint.Cap.ROUND);

        mPath = new Path();
        mBitmapPaint = new Paint(Paint.DITHER_FLAG);
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        mBitmap = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888);

    }

    @Override
    protected void onDraw(Canvas c) {
        canvas=c;
        canvas.drawBitmap(mBitmap, 0, 0, mBitmapPaint);

        mPaint.setColor(Color.BLUE);
        mPaint.setStrokeWidth(3);

        mPaint.setStrokeWidth(10);
        canvas.drawPath(mPath, mPaint);

        if(touching) {
            mPaint.setColor(Color.BLACK);

            canvas.drawCircle(mX, mY, 80, mPaint);

        }


    }

    private float mX=0;
    private float mY=0;
    private final float TOUCH_TOLERANCE = 4;
    private PointF curr;

    private void touch_start(float x, float y) {
        touching=true;


        mPath.reset();
        mPath.moveTo(x, y);
        mX = x;
        mY = y;

    }
    private void touch_move(float x, float y, boolean silent) {




        float rx = x - mX;
        float ry = y - mY;
        float dx = Math.abs(rx);
        float dy = Math.abs(ry);


        if (dx >= TOUCH_TOLERANCE || dy >= TOUCH_TOLERANCE) {
            if(!silent) mPath.quadTo(mX, mY, (x+mX)/2, (y+mY)/2);
            mX = x;
            mY = y;


            UDP_Client Client = new UDP_Client();
            int frx= (int) rx;
            int fry= (int) ry;
            Client.Message = "MRX"+frx+"Y"+fry;
            Client.Send();
        }


    }
    private void touch_up() {
        mPath.lineTo(mX, mY);
        // kill this so we don't double draw
        mPath.reset();
        touching=false;
    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {
        float x = event.getX();
        float y = event.getY();
        curr = new PointF(event.getX(), event.getY());
        double newDist = 0;


        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:

                downStart = System.currentTimeMillis();
                start.set(curr);
                touch_start(x, y);

                invalidate();
                break;
            case MotionEvent.ACTION_MOVE:

                int xDiff1 = (int) Math.abs(curr.x - start.x);
                int yDiff1 = (int) Math.abs(curr.y - start.y);


                //Log.d("onTouchEvent",xDiff1+" "+yDiff1+" "+CLICK);
                long thisTime = System.currentTimeMillis() - downStart;

                touch_move(x, y, false);

                invalidate();
                break;
            case MotionEvent.ACTION_UP:

                int xDiff = (int) Math.abs(curr.x - start.x);
                int yDiff = (int) Math.abs(curr.y - start.y);
                if (xDiff < CLICK && yDiff < CLICK) {

                    UDP_Client Client = new UDP_Client();
                    Client.Message = "CL";
                    Client.Send();

                }

                touch_up();
                invalidate();

                break;
        }
        return true;
    }
}
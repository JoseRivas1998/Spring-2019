using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EdgeScroll : MonoBehaviour
{
    [SerializeField]
    private AxisEnum horizontalAxis = AxisEnum.X;

    [SerializeField]
    private AxisEnum verticalAxis = AxisEnum.Z;

    public int margin = 32;
    public float camSpeed = 5.0f;
    public bool useEdgeScroll = true;
    public bool useKeyScroll = true;

    private Transform trans;
    private Vector3 velocity;

    public enum AxisEnum
    {
        X, Y, Z
    }

    private Vector3 horizontalVector;
    private Vector3 verticalVector;

    // Start is called before the first frame update
    void Start()
    {
        horizontalVector = AxisEnumToVector(horizontalAxis);
        verticalVector = AxisEnumToVector(verticalAxis);
        trans = GetComponent<Transform>();
        velocity = Vector3.zero;
    }

    // Update is called once per frame
    void Update()
    {
        float mouseX = Input.mousePosition.x;
        float mouseY = Input.mousePosition.y;
        velocity.Set(0, 0, 0);
        if (useEdgeScroll) MouseScroll(mouseX, mouseY);
        if (useKeyScroll) InputScroll();
        trans.position += velocity * Time.deltaTime;
    }

    /*
     * Precondition: velocity is zero
     */
    private void MouseScroll(float mouseX, float mouseY)
    {
        if (mouseX <= margin)
        {
            velocity -= horizontalVector * camSpeed;
        }
        else if (mouseX >= Screen.width - margin)
        {
            velocity += horizontalVector * camSpeed;
        }
        if (mouseY <= margin)
        {
            velocity -= verticalVector * camSpeed;
        }
        else if (mouseY >= Screen.height - margin)
        {
            velocity += verticalVector * camSpeed;
        }
    }

    private void InputScroll()
    {
        velocity += Input.GetAxis("Horizontal") * camSpeed * horizontalVector;
        velocity += Input.GetAxis("Vertical") * camSpeed * verticalVector;
    }

    Vector3 AxisEnumToVector(AxisEnum axis)
    {
        switch (axis)
        {
            // Yes I can use forward, right, and up but those are terrible names and I hate them
            case AxisEnum.X:
                return new Vector3(1, 0, 0);
            case AxisEnum.Y:
                return new Vector3(0, 1, 0);
            case AxisEnum.Z:
                return new Vector3(0, 0, 1);
            default:
                return Vector3.zero;

        }
    }

    public void updateHorizontalAxis(AxisEnum axis)
    {
        horizontalVector = AxisEnumToVector(axis);
    }

    public void updateVerticalAxis(AxisEnum axis)
    {
        verticalVector = AxisEnumToVector(axis);
    }

    void OnValidate()
    {
        if (horizontalAxis == verticalAxis)
        {
            horizontalAxis = AxisEnum.X;
            verticalAxis = AxisEnum.Z;
        }
    }

}

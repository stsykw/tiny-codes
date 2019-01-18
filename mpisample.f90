!!$
program mpitest
  use mpi
  implicit none
!!$ mpi variables
  integer:: id
  integer:: ierr
  integer:: rc
  integer,parameter::numprocs = 4
!!$
  integer,dimension(0:numprocs-1)::iseeds
  integer::iseed
  character(len=45),dimension(0:numprocs-1):: datfname
  character(len=*),parameter:: fnbase="test"

  call MPI_INIT(ierr)
  call MPI_COMM_RANK(MPI_COMM_WORLD,id,ierr)

  iseed = 123456789
  call make_seeds(iseed,iseeds,numprocs)
  call make_output_filename(datfname(id),id,fnbase)

  open(10,FILE=datfname(id))
  write(10,*) id,iseeds(id)

  call MPI_FINALIZE(rc)

end program mpitest

subroutine make_seeds(seed,iseeds,num)
  implicit none
  integer,intent(in):: num
  integer,intent(in):: seed
  integer,dimension(0:num),intent(out):: iseeds
  integer:: i
  integer,parameter:: ln = 1000
  integer,dimension(0:ln-1):: iy
  integer(kind=8),parameter:: aaa = Z'ffffffff'

  iy(0) = iand(seed,aaa)
  iseeds = 0

  do i=1,30
   iy(i) = 1812433253 * ieor(iy(i-1),ishft(iy(i-1),-30))+i
   iy(i) = iand(iy(i),aaa)
  end do
  do i=31,ln-1
   iy(i) = ieor(iy(i-31),iy(i-13))
  end do
  do i=0,num
   iseeds(i)=iy(ln-1-num+1+i)
  end do

end subroutine make_seeds


subroutine make_output_filename(datfname,id,fnbase)
  implicit none
  character(len=*),intent(out):: datfname
  integer,intent(in):: id
  character(len=*),intent(in):: fnbase
  character(len=4),parameter:: dada = ".dat"
  character(len=10)::tail

  write(tail,'(i4.4)') id
  write(datfname,'(10A)') fnbase(1:len_trim(fnbase)),dada,".p_",adjustl(tail)

end subroutine make_output_filename
